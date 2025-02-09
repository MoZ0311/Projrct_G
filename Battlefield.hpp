// Battlefield class

#pragma once

#include "MapBase.hpp"

class Battlefield : public MapBase
{
public:

	// 初期化処理
	static void Init();


	// 解放処理
	static void Release();

	// マップの侵入可能、不可能の導出
	Grid<bool> GetCanEnterGrid() const;

	// インスタンスのゲッター関数
	static Battlefield* GetBattlefieldInstance();

	// マップの二次元配列のゲッター関数
	Grid<int32> GetGrid() const;

private:

	// マップデータのセーブ処理
	void SaveMapData() override;

	// シングルトンクラスのインスタンスのポインタ
	static Battlefield* battlefieldInstance;
};
