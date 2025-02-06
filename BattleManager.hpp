// BattleManager class

#pragma once

#include "UnitBase.hpp"

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

	// 現在のターンのゲッター関数
	Turn GetCurrentTurn() const;

private:

	// コンストラクタ
	BattleManager();

	// デストラクタ
	~BattleManager();

	// シングルトンクラスのインスタンスのポインタ
	static BattleManager* battleManagerInstance;

	// 現在のターン
	Turn currentTurn;

	UnitBase* unitBase = nullptr;
};
