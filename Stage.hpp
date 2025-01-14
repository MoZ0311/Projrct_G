// Stage class

#pragma once

class Stage
{
public:

	// 初期化処理 void(void)
	static void Init();

	// 解放処理 void(void)
	static void Release();

	// 更新処理 void(void)
	void Update();

	// 描画処理 void(void)
	void Draw();

	// インスタンスのゲッター関数
	static Stage* GetStageInstance();

private:

	// コンストラクタ
	Stage();

	// デストラクタ
	~Stage();

	// シングルトンクラスのインスタンスのポインタ
	static Stage* stageInstance;
};
