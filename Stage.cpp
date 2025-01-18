// Stage class

#include "Stage.hpp"
#include "UI.hpp"

// インスタンスをnullptrで初期化
Stage* Stage::stageInstance = nullptr;

Stage::Stage()
{
	// png フォルダ内のファイルを列挙する
	for (const auto& filePath : FileSystem::DirectoryContents(U"tile/"))
	{
		// ファイル名が conifer と tree で始まるファイル（タイルではない）は除外する
		if (const FilePath baseName = FileSystem::BaseName(filePath);
			baseName.starts_with(U"conifer") || baseName.starts_with(U"tree"))
		{
			continue;
		}

		tileTextureArray << Texture{ filePath };
	}

	// 全部で 88 種類のタイルが読み込まれれば正常
	if (tileTextureArray.size() != 88)
	{
		throw Error{ U"ファイルの配置が不正です。" };
	}

	// タイルの種類
	Grid<int32> gr(Size{ N, N });
	grid = gr;
}

Stage::~Stage()
{

}

void Stage::Init()
{
	if (stageInstance != nullptr)
	{
		return;
	}

	stageInstance = new Stage();
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
		if (const auto index = ToIndex(Cursor::PosF(), columnQuads, rowQuads))
		{
			onMap = true;

			// マウスカーソルがあるタイルを取得
			mouseOveredTile = *index;

			// マウスの左ボタンが押されていたら
			if (MouseL.pressed())
			{
				// タイルの種類を更新する
				if (grid[*index] != UI::GetUIInstance()->GetTileTypeSelected())
				{
					grid[*index] = UI::GetUIInstance()->GetTileTypeSelected();
					Print << U"地形チェンジ!!";
				}
			}
		}
		else
		{
			onMap = false;
		}
	}
}


void Stage::Draw()
{
	// 上から順にタイルを描く
	for (int32 i = 0; i < (N * 2 - 1); ++i)
	{
		// x の開始インデックス
		const int32 xi = (i < (N - 1)) ? 0 : (i - (N - 1));

		// y の開始インデックス
		const int32 yi = (i < (N - 1)) ? i : (N - 1);

		// 左から順にタイルを描く
		for (int32 k = 0; k < (N - Abs(N - i - 1)); ++k)
		{
			// タイルのインデックス
			const Point index{ (xi + k), (yi - k) };

			// そのタイルの底辺中央の座標
			const Vec2 pos = ToTileBottomCenter(index, N);

			// 底辺中央を基準にタイルを描く
			tileTextureArray[grid[index]].draw(Arg::bottomCenter = pos);
		}
	}

	// マウスカーソルがあるタイルを強調表示する
	if (onMap)
	{
		ToTile(mouseOveredTile, N).draw(ColorF{ 1.0, 0.2 });
	}
	
	// マップ上のグリッドを表示する
	if (showGrid)
	{
		// 各列の四角形を描く
		for (const auto& columnQuad : columnQuads)
		{
			columnQuad.drawFrame(2);
		}

		// 各行の四角形を描く
		for (const auto& rowQuad : rowQuads)
		{
			rowQuad.drawFrame(2);
		}
	}
}

Vec2 Stage::ToTileBottomCenter(const Point& index, const int32 N)
{
	const int32 i = index.manhattanLength();
	const int32 xi = (i < (N - 1)) ? 0 : (i - (N - 1));
	const int32 yi = (i < (N - 1)) ? i : (N - 1);
	const int32 k = (index.manhattanDistanceFrom(Point{ xi, yi }) / 2);
	const double posX = ((i < (N - 1)) ? (i * -TileOffset.x) : ((i - 2 * N + 2) * TileOffset.x));
	const double posY = (i * TileOffset.y);
	return{ (posX + TileOffset.x * 2 * k), posY };
}

Quad Stage::ToTile(const Point& index, const int32 N)
{
	const Vec2 bottomCenter = ToTileBottomCenter(index, N);

	return Quad{
		bottomCenter.movedBy(0, -TileThickness).movedBy(0, -TileOffset.y * 2),
		bottomCenter.movedBy(0, -TileThickness).movedBy(TileOffset.x, -TileOffset.y),
		bottomCenter.movedBy(0, -TileThickness),
		bottomCenter.movedBy(0, -TileThickness).movedBy(-TileOffset.x, -TileOffset.y)
	};
}

Quad Stage::ToColumnQuad(const int32 x, const int32 N)
{
	return{
		ToTileBottomCenter(Point{ x, 0 }, N).movedBy(0, -TileThickness).movedBy(0, -TileOffset.y * 2),
		ToTileBottomCenter(Point{ x, 0 }, N).movedBy(0, -TileThickness).movedBy(TileOffset.x, -TileOffset.y),
		ToTileBottomCenter(Point{ x, (N - 1) }, N).movedBy(0, -TileThickness).movedBy(0, 0),
		ToTileBottomCenter(Point{ x, (N - 1) }, N).movedBy(0, -TileThickness).movedBy(-TileOffset.x, -TileOffset.y)
	};
}

Quad Stage::ToRowQuad(const int32 y, const int32 N)
{
	return{
		ToTileBottomCenter(Point{ 0, y }, N).movedBy(0, -TileThickness).movedBy(-TileOffset.x, -TileOffset.y),
		ToTileBottomCenter(Point{ 0, y }, N).movedBy(0, -TileThickness).movedBy(0, -TileOffset.y * 2),
		ToTileBottomCenter(Point{ (N - 1), y }, N).movedBy(0, -TileThickness).movedBy(TileOffset.x, -TileOffset.y),
		ToTileBottomCenter(Point{ (N - 1), y }, N).movedBy(0, -TileThickness).movedBy(0, 0)
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

Array<Texture> Stage::GetTileTextureArray()
{
	return tileTextureArray;
}
