// City class

#include "City.hpp"

// インスタンスをnullptrで初期化
City* City::cityInstance = nullptr;

City::City(GameScene* instance)
{
	gameSceneInstance = instance;
}

void City::Init(GameScene* instance)
{
	if (cityInstance != nullptr)
	{
		return;
	}

	cityInstance = new City(instance);
}

void City::Release()
{
	if (cityInstance != nullptr)
	{
		delete cityInstance;
		cityInstance = nullptr;
	}
}

void City::DrawTileHighlight()
{
	if (onMap && gameSceneInstance->GetIsEditing())
	{
		ToTile(mouseOveredTile, tileNum).draw(ColorF{ 1.0, 0.2 });
	}
}

void City::DrawGrid()
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

City* City::GetCityInstance()
{
	return cityInstance;
}
