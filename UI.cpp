// UI class

#include "UI.hpp"

#include "Stage.hpp"

UI* UI::UIInstance = nullptr;

UI::UI()
{
	onTileMenu = false;
}

UI::~UI()
{

}

void UI::Init()
{
	if (UIInstance != nullptr)
	{
		return;
	}

	UIInstance = new UI();
}

void UI::Release()
{
	if (UIInstance != nullptr)
	{
		delete UIInstance;
		UIInstance = nullptr;
	}
}

void UI::Update()
{
	// タイルメニュー上にカーソルがあるか
	onTileMenu = TileMenuRoundRect.mouseOver();

	// 各タイル
	for (int32 y = 0; y < 4; ++y)
	{
		for (int32 x = 0; x < 22; ++x)
		{
			// タイルの長方形
			const Rect rect{ (TileMenuRect.x + x * 56), (20 + y * 50), 56, 50 };

			// タイルの種類
			const int32 tileType = (y * 22 + x);

			// タイルの上にマウスカーソルがあれば
			if (rect.mouseOver())
			{
				// カーソルを手のアイコンにする
				Cursor::RequestStyle(CursorStyle::Hand);

				// 左クリックされたら		
				if (MouseL.down())
				{
					// 選択しているタイルの種類を更新する
					tileTypeSelected = tileType;
					ClearPrint();
				}
			}
		}
	}
}

void UI::Draw()
{
	// UI背景
	TileMenuRoundRect.draw();

	// 各タイル
	for (int32 y = 0; y < 4; ++y)
	{
		for (int32 x = 0; x < 22; ++x)
		{
			// タイルの長方形
			const Rect rect{ (TileMenuRect.x + x * 56), (20 + y * 50), 56, 50};

			// タイルの種類
			const int32 tileType = (y * 22 + x);

			// 現在選択されているタイルであれば
			if (tileType == tileTypeSelected)
			{
				// 背景を灰色にする
				rect.draw(ColorF{ 0.85 });
			}

			// タイルを表示する
			Stage::GetStageInstance()->GetTileTextureArray()[tileType].scaled(0.5).drawAt(rect.center());
		}
	}
}

UI* UI::GetUIInstance()
{
	return UIInstance;
}

bool UI::GetOnTileMenu()
{
	return onTileMenu;
}

int32 UI::GetTileTypeSelected()
{
	return tileTypeSelected;
}
