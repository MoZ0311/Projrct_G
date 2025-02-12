// TownField class

#include "Townfield.hpp"

// インスタンスをnullptrで初期化
Townfield* Townfield::townFieldInstance = nullptr;

Townfield::Townfield(GameScene* instance)
{
	gameSceneInstance = instance;
}

void Townfield::Init(GameScene* instance)
{
	if (townFieldInstance != nullptr)
	{
		return;
	}

	townFieldInstance = new Townfield(instance);
}

void Townfield::Release()
{
	if (townFieldInstance != nullptr)
	{
		delete townFieldInstance;
		townFieldInstance = nullptr;
	}
}

void Townfield::SetMapDataFilePath()
{
	mapDataFile = TOWNFIELD_DATA_FILE;
}

void Townfield::DrawTileHighlight()
{
	if (onMap && gameSceneInstance->GetIsEditing())
	{
		ToTile(mouseOveredTile, TILE_NUM).draw(ColorF{ 1.0, 0.2 });
	}
}

void Townfield::DrawGrid()
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

Townfield* Townfield::GetTownFieldInstance()
{
	return townFieldInstance;
}

Array<int32> Townfield::GetMapStatus()
{
	// マップの合計ステータス { Moisture, Urban, Nature, Rough }
	Array<int32> mapStatus{ 0, 0, 0, 0 };

	for (int32 row = 0; row < grid.height(); ++row)
	{
		for (int32 column = 0; column < grid.width(); ++column)
		{
			for (int32 statusIndex = 0; statusIndex < mapStatus.size(); ++statusIndex)
			{
				// CSVのヘッダ行を無視するため、+1
				int32 tileRow = grid[row][column] + 1;

				// CSVの"Name"列を無視するため、+1
				int32 tileColumn = statusIndex + 1;

				mapStatus[statusIndex] += Parse<int32>(tileStatus[tileRow][tileColumn]);
				if (mapStatus[statusIndex] < 0)
				{
					mapStatus[statusIndex] = 0;
				}
			}
		}
	}
	return mapStatus;
}
