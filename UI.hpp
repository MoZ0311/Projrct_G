// UI class

#pragma once

#include "GameScene.hpp"

class UI
{
public:

	// 初期化処理
	static void Init();

	// 解放処理
	static void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

	// インスタンスのゲッター関数
	static UI* GetUIInstance();

	// カーソル有無の取得
	bool GetOnTileMenu() const;

	// 選択されたタイルの取得
	int32 GetTileTypeSelected() const;

private:

	// コンストラクタ
	UI();

	// デストラクタ
	~UI();

	// シングルトンクラスのインスタンスのポインタ
	static UI* UIInstance;

	// GameScene クラスのインスタンスのポインタ
	GameScene* gameSceneInstance;

	// 選択したタイルの背景用四角形
	const Size SELECTED_TILE_BACK{ 56, 50 };

	// UIタイルの表示数
	const Size UI_TILE_DISPLAY{ 22, 4 };

	// タイルメニューの四角形の原型
	const Rect TILE_MENU_RECT{ Arg::topCenter(Scene::Center().x, 20), (SELECTED_TILE_BACK.x * UI_TILE_DISPLAY.x), (SELECTED_TILE_BACK.y * UI_TILE_DISPLAY.y) };

	// タイルメニューの四角形
	const RoundRect TILE_MENU_ROUND_RECT = TILE_MENU_RECT.stretched(10).rounded(8);

	// タイルメニュー上にカーソルがあるか
	bool onTileMenu;

	// タイルメニューで選択されているタイルの種類
	int32 tileTypeSelected;
};
