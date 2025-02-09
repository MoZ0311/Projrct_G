// Battlefield class

#include "Battlefield.hpp"

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

void Battlefield::SaveMapData()
{
	// 戦場のマップデータは上書きさせない
	return;
}

Grid<bool> Battlefield::GetCanEnterGrid() const
{
	// マップと同じサイズのbool型の二次元配列を作成 (0 : 通行不可, 1 : 通行可)
	Grid<bool> canEnterGrid(grid.size(), 1);

	// CSVファイルの移動可不可に当たる列
	constexpr int32 COLUMN_CAN_ENTER = 5;

	// 上から地形をチェック
	for (int32 row = 0; row < grid.height(); row++)
	{
		for (int32 column = 0; column < grid.width(); column++)
		{
			// CSVの当該データをbool型として代入
			canEnterGrid[row][column] = Parse<int32>(tileStatus[grid[row][column] + 1][COLUMN_CAN_ENTER]) == 1 ? true : false;
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
