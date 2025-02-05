// BattleManager class

#pragma once

class BattleManager
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
	static BattleManager* GetBattleManagerInstance();

private:

	// コンストラクタ
	BattleManager();

	// デストラクタ
	~BattleManager();

	// シングルトンクラスのインスタンスのポインタ
	static BattleManager* battleManagerInstance;
};
