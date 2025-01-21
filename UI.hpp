// UI class

#pragma once

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
	bool GetOnTileMenu();

	// 選択されたタイルの取得
	int32 GetTileTypeSelected();

private:

	// コンストラクタ
	UI();

	// デストラクタ
	~UI();

	// シングルトンクラスのインスタンスのポインタ
	static UI* UIInstance;

	// タイルメニューの四角形の原型
	const Rect TileMenuRect{ Arg::topCenter(Scene::Center().x, 20), (56 * 22), (50 * 4) };

	// タイルメニューの四角形
	const RoundRect TileMenuRoundRect = TileMenuRect.stretched(10).rounded(8);

	// タイルメニュー上にカーソルがあるか
	bool onTileMenu;

	// タイルメニューで選択されているタイルの種類
	int32 tileTypeSelected = 30;
};
