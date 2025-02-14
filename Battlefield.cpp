// Battlefield class

#include "Battlefield.hpp"
#include "UnitManager.hpp"

// インスタンスをnullptrで初期化
Battlefield* Battlefield::battlefieldInstance = nullptr;

void Battlefield::Init()
{
	if (battlefieldInstance != nullptr)
	{
		return;
	}
	battlefieldInstance = new Battlefield();
}

void Battlefield::Release()
{
	if (battlefieldInstance != nullptr)
	{
		delete battlefieldInstance;
		battlefieldInstance = nullptr;
	}
}

void Battlefield::Update()
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
			clickedTileIndex = mouseOveredTile;
		}
	}
	else
	{
		onMap = false;
	}
}

void Battlefield::DrawMoveRange(Grid<int32> distanceGrid, int32 movePower)
{
	// マップの上から順に評価
	for (int32 row = 0; row < grid.height(); ++row)
	{
		for (int32 column = 0; column < grid.width(); ++column)
		{
			ColorF highlightColor{};
			if (distanceGrid[row][column] <= movePower)
			{
				highlightColor = CLEAR_BLUE;
			}
			else
			{
				highlightColor = CLEAR_RED;
			}
			ToTile(Point{ column, row }, TILE_NUM).stretched(GRID_STRETCH).draw(highlightColor).drawFrame(1, 0, highlightColor);
		}
	}
}

void Battlefield::SetMapDataFilePath()
{
	mapDataFile = BATTLEFIELD_DATA_FILE;
}

void Battlefield::SaveMapData()
{
	// 戦場のマップデータは上書きさせない
	return;
}

void Battlefield::DrawGrid()
{
	// グリッド描画は別で行う
	return;
}

Grid<bool> Battlefield::GetCanEnterGrid(Point gridPosition) const
{
	// マップと同じサイズのbool型の二次元配列を作成 (0 : 通行不可, 1 : 通行可)
	constexpr int32 CAN_ENTER = 1;
	Grid<bool> canEnterGrid(grid.size(), CAN_ENTER);

	// CSVファイルの移動可不可を記した列
	constexpr int32 COLUMN_CAN_ENTER = 5;

	// ユニットが立っているグリッド座標配列
	Array<Point> unitPositionArray = UnitManager::GetUnitManagerInstance()->GetAllUnitPositionArray();

	// 上から地形をチェック
	for (int32 row = 0; row < grid.height(); ++row)
	{
		for (int32 column = 0; column < grid.width(); ++column)
		{
			// CSVのヘッダを無視するため、+1
			int32 tileRow = grid[row][column] + 1;

			// 侵入可能な地形、かつそこにユニットがいないor自分が立っている場合に侵入可能
			canEnterGrid[row][column] = Parse<int32>(tileStatus[tileRow][COLUMN_CAN_ENTER]) == CAN_ENTER &&
			(!unitPositionArray.contains(Point{ column, row }) || gridPosition == Point{ column, row })
				? true : false;
		}
	}

	return canEnterGrid;
}

Battlefield* Battlefield::GetBattlefieldInstance()
{
	return battlefieldInstance;
}

Grid<int32> Battlefield::GetGrid() const
{
	return grid;
}

Point Battlefield::GetClickedTileIndex() const
{
	return clickedTileIndex;
}

bool Battlefield::GetOnMap() const
{
	return onMap;
}
