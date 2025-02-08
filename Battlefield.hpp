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

	// インスタンスのゲッター関数
	static Battlefield* GetBattlefieldInstance();

private:

	// マップデータのセーブ処理
	void SaveMapData() override;

	// シングルトンクラスのインスタンスのポインタ
	static Battlefield* battlefieldInstance;
};
