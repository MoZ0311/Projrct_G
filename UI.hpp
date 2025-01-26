// UI class

#pragma once

#include "GameScene.hpp"

class UI
{
public:

	// 初期化処理
	static void Init(GameScene* instance);

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
	UI(GameScene* instance);

	// デストラクタ
	~UI();

	// シングルトンクラスのインスタンスのポインタ
	static UI* UIInstance;

	// GameScene クラスのインスタンスのポインタ
	GameScene* gameSceneInstance;

	// タイルメニューの四角形の原型
	const Rect TileMenuRect{ Arg::topCenter(Scene::Center().x, 20), (56 * 22), (50 * 4) };

	// タイルメニューの四角形
	const RoundRect TileMenuRoundRect = TileMenuRect.stretched(10).rounded(8);

	// タイルメニュー上にカーソルがあるか
	bool onTileMenu;

	// タイルメニューで選択されているタイルの種類
	int32 tileTypeSelected;
};
