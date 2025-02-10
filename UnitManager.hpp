// UnitManager class

#pragma once

#include "UnitBase.hpp"

class UnitManager
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

	// ユニットの生成処理
	void InstantiateUnit();

	// インスタンスのゲッター関数
	static UnitManager* GetBattleManagerInstance();

	// 現在のターンのゲッター関数
	Turn GetCurrentTurn() const;

private:

	// コンストラクタ
	UnitManager();

	// デストラクタ
	~UnitManager();

	// シングルトンクラスのインスタンスのポインタ
	static UnitManager* battleManagerInstance;

	// 現在のターン
	Turn currentTurn;

	// 自軍ユニットのインスタンス配列
	Array<UnitBase*> playerUnitInstanceArray;

	// 敵軍ユニットのインスタンス配列
	Array<UnitBase*> enemyUnitInstanceArray;

	// 全ユニットのインスタンス配列
	Array<UnitBase*> allUnitInstanceArray;
};
