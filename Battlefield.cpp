// Battlefield class

#include "Battlefield.hpp"

// インスタンスをnullptrで初期化
Battlefield* Battlefield::battlefieldInstance = nullptr;

void Battlefield::Init()
{
	if (battlefieldInstance != nullptr)
	{
		return;
	}
	battlefieldInstance = new Battlefield();
}

void Battlefield::Release()
{
	if (battlefieldInstance != nullptr)
	{
		delete battlefieldInstance;
		battlefieldInstance = nullptr;
	}
}

void Battlefield::SaveMapData()
{
	// 戦場のマップデータは上書きさせない
	return;
}

Battlefield* Battlefield::GetBattlefieldInstance()
{
	return battlefieldInstance;
}
