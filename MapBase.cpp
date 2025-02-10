// MapBase class

#include "MapBase.hpp"

#include "UI.hpp"

MapBase::MapBase()
{
	// tile フォルダ内のファイルを列挙する
	for (const auto& filePath : FileSystem::DirectoryContents(U"tile/"))
	{
		tileTextureArray << LoadPremultipliedTexture(filePath);
	}

	// 全部で 88 種類のタイルが読み込まれれば正常
	if (tileTextureArray.size() != 18)
	{
		throw Error{ U"ファイルの配置が不正です。" };
	}

	tileNum = 12;
	onMap = false;
	mouseOveredTile = {};
}

MapBase::~MapBase()
{

}

void MapBase::LoadMapData()
{
	SetMapDataFilePath();

	// CSVファイルの読み込み
	mapData.load(mapDataFile);
	if (!mapData)
	{
		throw Error{ mapDataFile + U"が読み込めません" };
	}

	tileStatus.load(TILE_STATUS_DATA_FILE);
	if (!tileStatus)
	{
		throw Error{ TILE_STATUS_DATA_FILE + U"が読み込めません" };
	}

	tileNum = 12;

	// 行列の四角形を算出
	columnQuadArray = MakeColumnQuads(tileNum);
	rowQuadArray = MakeRowQuads(tileNum);

	// タイルの初期化
	grid = { Size(tileNum, tileNum), -1 };

	// CSVファイルの内容をマップに反映
	for (int32 row = 0; row < grid.height(); ++row)
	{
		for (int32 column = 0; column < grid.width(); ++column)
		{
			grid[row][column] = Parse<int32>(mapData[row][column]);
		}
	}
}

void MapBase::Update()
{
	// マウスカーソルがタイルメニュー上に無ければ
	if (!UI::GetUIInstance()->GetOnTileMenu())
	{
		// マウスカーソルがマップ上のどのタイルの上にあるかを取得する
		if (const auto index = ToIndex(Cursor::PosF(), columnQuadArray, rowQuadArray))
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

	// Ctrl + Sでセーブを行う
	if (KeyControl.pressed() && KeyS.down())
	{
		SaveMapData();
	}
}

void MapBase::Draw()
{
	{
		// 乗算済みアルファ用のブレンドステートを適用する
		const ScopedRenderStates2D blend{ BlendState::Premultiplied };

		// 上から順にタイルを描く
		for (int32 i = 0; i < (tileNum * 2 - 1); ++i)
		{
			// x の開始インデックス
			const int32 xi = (i < (tileNum - 1)) ? 0 : (i - (tileNum - 1));

			// y の開始インデックス
			const int32 yi = (i < (tileNum - 1)) ? i : (tileNum - 1);

			// 左から順にタイルを描く
			for (int32 k = 0; k < (tileNum - Abs(tileNum - i - 1)); ++k)
			{
				// タイルのインデックス
				const Point index{ (xi + k), (yi - k) };

				// そのタイルの底辺中央の座標
				const Vec2 pos = ToTileBottomCenter(index, tileNum);

				// 底辺中央を基準にタイルを描く
				tileTextureArray[grid[index]].draw(Arg::bottomCenter = pos);
			}
		}
	}

	// タイルを強調表示する
	DrawTileHighlight();

	// マップ上のグリッドを表示する
	DrawGrid();
}

void MapBase::SetMapDataFilePath()
{
	//mapDataFile = TOWNFIELD_DATA_FILE;
}

bool MapBase::MapEqualsCSV()
{
	// CSVファイルの内容とマップを比較
	for (int32 row = 0; row < grid.height(); ++row)
	{
		for (int32 column = 0; column < grid.width(); ++column)
		{
			// CSVとの差異があった時点でreturn
			if (grid[row][column] != Parse<int32>(mapData[row][column]))
			{
				return false;
			}
		}
	}

	return true;
}

void MapBase::SaveMapData()
{
	ClearPrint();

	// マップの内容をCSVファイルに反映
	for (int32 row = 0; row < grid.height(); ++row)
	{
		for (int32 column = 0; column < grid.width(); ++column)
		{
			mapData[row][column] = Format(grid[row][column]);
		}
	}

	// CSVを保存する
	mapData.save(mapDataFile);

	Print << U"セーブしました";
}

void MapBase::DrawTileHighlight()
{
	if (onMap)
	{
		ToTile(mouseOveredTile, tileNum).draw(ColorF{ 1.0, 0.5 });
	}
}

void MapBase::DrawGrid()
{
	// グリッドの幅
	double frameThickness = 1;

	// 各列の四角形を描く
	for (const auto& columnQuad : columnQuadArray)
	{
		columnQuad.drawFrame(frameThickness);
	}

	// 各行の四角形を描く
	for (const auto& rowQuad : rowQuadArray)
	{
		rowQuad.drawFrame(frameThickness);
	}
}

Vec2 MapBase::ToTileBottomCenter(const Point& index, const int32 N) const
{
	const int32 i = index.manhattanLength();
	const int32 xi = (i < (N - 1)) ? 0 : (i - (N - 1));
	const int32 yi = (i < (N - 1)) ? i : (N - 1);
	const int32 k = (index.manhattanDistanceFrom(Point{ xi, yi }) / 2);
	const double posX = ((i < (N - 1)) ? (i * -TILE_OFFSET.x) : ((i - 2 * N + 2) * TILE_OFFSET.x));
	const double posY = (i * TILE_OFFSET.y);
	return{ (posX + TILE_OFFSET.x * 2 * k), posY };
}

Quad MapBase::ToTile(const Point& index, const int32 N) const
{
	const Vec2 bottomCenter = ToTileBottomCenter(index, N);

	return Quad{
		bottomCenter.movedBy(0, -TILE_THICKNESS).movedBy(0, -TILE_OFFSET.y * 2),
		bottomCenter.movedBy(0, -TILE_THICKNESS).movedBy(TILE_OFFSET.x, -TILE_OFFSET.y),
		bottomCenter.movedBy(0, -TILE_THICKNESS),
		bottomCenter.movedBy(0, -TILE_THICKNESS).movedBy(-TILE_OFFSET.x, -TILE_OFFSET.y)
	};
}

Quad MapBase::ToColumnQuad(const int32 x, const int32 N)
{
	return{
		ToTileBottomCenter(Point{ x, 0 }, N).movedBy(0, -TILE_THICKNESS).movedBy(0, -TILE_OFFSET.y * 2),
		ToTileBottomCenter(Point{ x, 0 }, N).movedBy(0, -TILE_THICKNESS).movedBy(TILE_OFFSET.x, -TILE_OFFSET.y),
		ToTileBottomCenter(Point{ x, (N - 1) }, N).movedBy(0, -TILE_THICKNESS).movedBy(0, 0),
		ToTileBottomCenter(Point{ x, (N - 1) }, N).movedBy(0, -TILE_THICKNESS).movedBy(-TILE_OFFSET.x, -TILE_OFFSET.y)
	};
}

Quad MapBase::ToRowQuad(const int32 y, const int32 N)
{
	return{
		ToTileBottomCenter(Point{ 0, y }, N).movedBy(0, -TILE_THICKNESS).movedBy(-TILE_OFFSET.x, -TILE_OFFSET.y),
		ToTileBottomCenter(Point{ 0, y }, N).movedBy(0, -TILE_THICKNESS).movedBy(0, -TILE_OFFSET.y * 2),
		ToTileBottomCenter(Point{ (N - 1), y }, N).movedBy(0, -TILE_THICKNESS).movedBy(TILE_OFFSET.x, -TILE_OFFSET.y),
		ToTileBottomCenter(Point{ (N - 1), y }, N).movedBy(0, -TILE_THICKNESS).movedBy(0, 0)
	};
}

Array<Quad> MapBase::MakeColumnQuads(const int32 N)
{
	Array<Quad> quads;

	for (int32 x = 0; x < N; ++x)
	{
		quads << ToColumnQuad(x, N);
	}

	return quads;
}

Array<Quad> MapBase::MakeRowQuads(const int32 N)
{
	Array<Quad> quads;

	for (int32 y = 0; y < N; ++y)
	{
		quads << ToRowQuad(y, N);
	}

	return quads;
}

Optional<Point> MapBase::ToIndex(const Vec2& pos, const Array<Quad>& columnQuads, const Array<Quad>& rowQuads)
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

Texture MapBase::LoadPremultipliedTexture(FilePathView path)
{
	Image image{ path };
	Color* p = image.data();
	const Color* const pEnd = (p + image.num_pixels());
	while (p != pEnd)
	{
		p->r = static_cast<uint8>((static_cast<uint16>(p->r) * p->a) / 255);
		p->g = static_cast<uint8>((static_cast<uint16>(p->g) * p->a) / 255);
		p->b = static_cast<uint8>((static_cast<uint16>(p->b) * p->a) / 255);
		++p;
	}
	return Texture{ image, TextureDesc::Mipped };
}

Array<Texture> MapBase::GetTileTextureArray()
{
	return tileTextureArray;
}
