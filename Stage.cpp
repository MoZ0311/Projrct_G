// Stage class

#include "Stage.hpp"

#include "UI.hpp"

// インスタンスをnullptrで初期化
Stage* Stage::stageInstance = nullptr;

Stage::Stage(GameScene* instance)
{
	// GameScene クラスのインスタンスを格納
	gameSceneInstance = instance;

	// タイルの初期化
	grid = { Size(TILE_NUM, TILE_NUM), -1 };

	// CSVファイルの読み込み
	csv.load(MAP_DATA_FILE);
	if (!csv)
	{
		throw Error{ U"CSVファイルが読み込めません" };
	}

	// CSVファイルの内容をマップに反映
	for (int32 column = 0; column < TILE_NUM; column++)
	{
		for (int32 row = 0; row < TILE_NUM; row++)
		{
			grid[column][row] = Parse<int32>(csv[column][row]);
		}
	}

	onMap = false;
}

Stage::~Stage()
{

}

void Stage::Init(GameScene* instance)
{
	if (stageInstance != nullptr)
	{
		return;
	}

	stageInstance = new Stage(instance);
}

void Stage::Release()
{
	if (stageInstance != nullptr)
	{
		delete stageInstance;
		stageInstance = nullptr;
	}
}

void Stage::Update()
{
	// マウスカーソルがタイルメニュー上に無ければ
	if (!UI::GetUIInstance()->GetOnTileMenu())
	{
		// マウスカーソルがマップ上のどのタイルの上にあるかを取得する
		if (const auto index = ToIndex(Cursor::PosF(), COLUMN_QUADS, ROW_QUADS))
		{
			onMap = true;

			// マウスカーソルがあるタイルを取得
			mouseOveredTile = *index;

			// マウスの左ボタンが押されていたら
			if (MouseL.pressed() && !MouseR.pressed())
			{
				int32 selectedTyle = UI::GetUIInstance()->GetTileTypeSelected();

				// タイルの種類を更新する
				if (grid[*index] != selectedTyle)
				{
					grid[*index] = selectedTyle;
				}
			}
		}
		else
		{
			onMap = false;
		}
	}

	// Ctrl + S
	if (KeyControl.pressed() && KeyS.down())
	{
		ClearPrint();

		// マップの内容をCSVファイルに反映
		for (int32 column = 0; column < TILE_NUM; column++)
		{
			for (int32 row = 0; row < TILE_NUM; row++)
			{
				csv[column][row] = Format(grid[column][row]);
			}
		}

		// CSVを保存する
		csv.save(MAP_DATA_FILE);

		Print << U"セーブしました";
	}
}


void Stage::Draw()
{
	{
		// 乗算済みアルファ用のブレンドステートを適用する
		const ScopedRenderStates2D blend{ BlendState::Premultiplied };

		// 上から順にタイルを描く
		for (int32 i = 0; i < (TILE_NUM * 2 - 1); ++i)
		{
			// x の開始インデックス
			const int32 xi = (i < (TILE_NUM - 1)) ? 0 : (i - (TILE_NUM - 1));

			// y の開始インデックス
			const int32 yi = (i < (TILE_NUM - 1)) ? i : (TILE_NUM - 1);

			// 左から順にタイルを描く
			for (int32 k = 0; k < (TILE_NUM - Abs(TILE_NUM - i - 1)); ++k)
			{
				// タイルのインデックス
				const Point index{ (xi + k), (yi - k) };

				// そのタイルの底辺中央の座標
				const Vec2 pos = ToTileBottomCenter(index, TILE_NUM);

				// 底辺中央を基準にタイルを描く
				gameSceneInstance->GetTileTextureArray()[grid[index]].draw(Arg::bottomCenter = pos);
			}
		}
	}

	// マウスカーソルがあるタイルを強調表示する
	if (onMap && gameSceneInstance->GetIsEditing())
	{
		ToTile(mouseOveredTile, TILE_NUM).draw(ColorF{ 1.0, 0.2 });
	}
	
	// マップ上のグリッドを表示する
	if (gameSceneInstance->GetIsEditing())
	{
		// 各列の四角形を描く
		for (const auto& columnQuad : COLUMN_QUADS)
		{
			columnQuad.drawFrame(2);
		}

		// 各行の四角形を描く
		for (const auto& rowQuad : ROW_QUADS)
		{
			rowQuad.drawFrame(2);
		}
	}
}

bool Stage::MapEqualsCSV()
{
	// CSVファイルの内容とマップを比較
	for (int32 column = 0; column < TILE_NUM; column++)
	{
		for (int32 row = 0; row < TILE_NUM; row++)
		{
			// CSVとの差異があった時点でreturn
			if (grid[column][row] != Parse<int32>(csv[column][row]))
			{
				return false;
			}
		}
	}

	return true;
}

Vec2 Stage::ToTileBottomCenter(const Point& index, const int32 N) const
{
	const int32 i = index.manhattanLength();
	const int32 xi = (i < (N - 1)) ? 0 : (i - (N - 1));
	const int32 yi = (i < (N - 1)) ? i : (N - 1);
	const int32 k = (index.manhattanDistanceFrom(Point{ xi, yi }) / 2);
	const double posX = ((i < (N - 1)) ? (i * -TILE_OFFSET.x) : ((i - 2 * N + 2) * TILE_OFFSET.x));
	const double posY = (i * TILE_OFFSET.y);
	return{ (posX + TILE_OFFSET.x * 2 * k), posY };
}

Quad Stage::ToTile(const Point& index, const int32 N)
{
	const Vec2 bottomCenter = ToTileBottomCenter(index, N);

	return Quad{
		bottomCenter.movedBy(0, -TILE_THICKNESS).movedBy(0, -TILE_OFFSET.y * 2),
		bottomCenter.movedBy(0, -TILE_THICKNESS).movedBy(TILE_OFFSET.x, -TILE_OFFSET.y),
		bottomCenter.movedBy(0, -TILE_THICKNESS),
		bottomCenter.movedBy(0, -TILE_THICKNESS).movedBy(-TILE_OFFSET.x, -TILE_OFFSET.y)
	};
}

Quad Stage::ToColumnQuad(const int32 x, const int32 N)
{
	return{
		ToTileBottomCenter(Point{ x, 0 }, N).movedBy(0, -TILE_THICKNESS).movedBy(0, -TILE_OFFSET.y * 2),
		ToTileBottomCenter(Point{ x, 0 }, N).movedBy(0, -TILE_THICKNESS).movedBy(TILE_OFFSET.x, -TILE_OFFSET.y),
		ToTileBottomCenter(Point{ x, (N - 1) }, N).movedBy(0, -TILE_THICKNESS).movedBy(0, 0),
		ToTileBottomCenter(Point{ x, (N - 1) }, N).movedBy(0, -TILE_THICKNESS).movedBy(-TILE_OFFSET.x, -TILE_OFFSET.y)
	};
}

Quad Stage::ToRowQuad(const int32 y, const int32 N)
{
	return{
		ToTileBottomCenter(Point{ 0, y }, N).movedBy(0, -TILE_THICKNESS).movedBy(-TILE_OFFSET.x, -TILE_OFFSET.y),
		ToTileBottomCenter(Point{ 0, y }, N).movedBy(0, -TILE_THICKNESS).movedBy(0, -TILE_OFFSET.y * 2),
		ToTileBottomCenter(Point{ (N - 1), y }, N).movedBy(0, -TILE_THICKNESS).movedBy(TILE_OFFSET.x, -TILE_OFFSET.y),
		ToTileBottomCenter(Point{ (N - 1), y }, N).movedBy(0, -TILE_THICKNESS).movedBy(0, 0)
	};
}

Array<Quad> Stage::MakeColumnQuads(const int32 N)
{
	Array<Quad> quads;

	for (int32 x = 0; x < N; ++x)
	{
		quads << ToColumnQuad(x, N);
	}

	return quads;
}

Array<Quad> Stage::MakeRowQuads(const int32 N)
{
	Array<Quad> quads;

	for (int32 y = 0; y < N; ++y)
	{
		quads << ToRowQuad(y, N);
	}

	return quads;
}

Optional<Point> Stage::ToIndex(const Vec2& pos, const Array<Quad>& columnQuads, const Array<Quad>& rowQuads)
{
	int32 x = -1, y = -1;

	// タイルの列インデックスを調べる
	for (int32 i = 0; i < columnQuads.size(); ++i)
	{
		if (columnQuads[i].intersects(pos))
		{
			x = i;
			break;
		}
	}

	// タイルの行インデックスを調べる
	for (int32 i = 0; i < rowQuads.size(); ++i)
	{
		if (rowQuads[i].intersects(pos))
		{
			y = i;
			break;
		}
	}

	// インデックスが -1 の場合、タイル上にはない
	if ((x == -1) || (y == -1))
	{
		return none;
	}

	return Point{ x, y };
}

Stage* Stage::GetStageInstance()
{
	return stageInstance;
}

Polygon Stage::GetMapCollider() const
{
	return MAP_COLLIDER;
}
