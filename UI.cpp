// UI class

#include "UI.hpp"

#include "Townfield.hpp"
#include "Battlefield.hpp"

UI* UI::UIInstance = nullptr;

UI::UI()
{
	onTileMenu = false;
	tileTypeSelected = 30;
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
	onTileMenu = TILE_MENU_ROUND_RECT.mouseOver();

	// 各タイル
	for (int32 y = 0; y < UI_TILE_DISPLAY.y; ++y)
	{
		for (int32 x = 0; x < UI_TILE_DISPLAY.x; ++x)
		{
			// タイルのマウス用当たり判定
			const Rect rect{ (TILE_MENU_RECT.x + x * SELECTED_TILE_BACK.x), (20 + y * SELECTED_TILE_BACK.y), SELECTED_TILE_BACK };

			// タイルの種類
			const int32 tileType = (y * UI_TILE_DISPLAY.x + x);

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
				}
			}
		}
	}
}

void UI::Draw()
{
	// UI背景
	TILE_MENU_ROUND_RECT.draw();

	{
		// 乗算済みアルファ用のブレンドステートを適用する
		const ScopedRenderStates2D blend{ BlendState::Premultiplied };

		// 各タイル
		for (int32 y = 0; y < UI_TILE_DISPLAY.y; ++y)
		{
			for (int32 x = 0; x < UI_TILE_DISPLAY.x; ++x)
			{
				// タイルの長方形
				const Rect rect{ (TILE_MENU_RECT.x + x * SELECTED_TILE_BACK.x), (20 + y * SELECTED_TILE_BACK.y), SELECTED_TILE_BACK };

				// タイルの種類
				const int32 tileType = (y * UI_TILE_DISPLAY.x + x);

				// 現在選択されているタイルであれば
				if (tileType == tileTypeSelected)
				{
					// 背景を灰色にする
					rect.draw(ColorF{ 0.85 });
				}

				// タイルを表示する
				Array<Texture> tileTextureArray{};
				if (Townfield::GetTownFieldInstance() != nullptr)
				{
					tileTextureArray = Townfield::GetTownFieldInstance()->GetTileTextureArray();
				}
				else if (Battlefield::GetBattlefieldInstance() != nullptr)
				{
					tileTextureArray = Battlefield::GetBattlefieldInstance()->GetTileTextureArray();
				}
				tileTextureArray[tileType].scaled(0.5).drawAt(rect.center());
			}
		}
	}
}

UI* UI::GetUIInstance()
{
	return UIInstance;
}

bool UI::GetOnTileMenu() const
{
	return onTileMenu;
}

int32 UI::GetTileTypeSelected() const
{
	return tileTypeSelected;
}
