// TownField class

#include "TownField.hpp"

// インスタンスをnullptrで初期化
TownField* TownField::townFieldInstance = nullptr;

TownField::TownField(GameScene* instance)
{
	gameSceneInstance = instance;
}

void TownField::Init(GameScene* instance)
{
	if (townFieldInstance != nullptr)
	{
		return;
	}

	townFieldInstance = new TownField(instance);
}

void TownField::Release()
{
	if (townFieldInstance != nullptr)
	{
		delete townFieldInstance;
		townFieldInstance = nullptr;
	}
}

void TownField::SetMapDataFilePath()
{
	mapDataFile = TOWNFIELD_DATA_FILE;
}

void TownField::DrawTileHighlight()
{
	if (onMap && gameSceneInstance->GetIsEditing())
	{
		ToTile(mouseOveredTile, tileNum).draw(ColorF{ 1.0, 0.2 });
	}
}

void TownField::DrawGrid()
{
	if (gameSceneInstance->GetIsEditing())
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
}

TownField* TownField::GetTownFieldInstance()
{
	return townFieldInstance;
}

Array<int32> TownField::GetMapStatus() const
{
	// マップの合計ステータス { Moisture, Urban, Nature, Rough }
	Array<int32> mapStatus{ 0, 0, 0, 0 };

	for (int32 row = 0; row < grid.height(); row++)
	{
		for (int32 column = 0; column < grid.width(); column++)
		{
			for (int32 statusIndex = 0; statusIndex < mapStatus.size(); statusIndex++)
			{
				mapStatus[statusIndex] += Parse<int32>(tileStatus[grid[row][column] + 1][statusIndex + 1]);
				if (mapStatus[statusIndex] < 0)
				{
					mapStatus[statusIndex] = 0;
				}
			}
		}
	}
	return mapStatus;
}
