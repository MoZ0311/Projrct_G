// BattleManager class

#include "BattleManager.hpp"

// インスタンスをnullptrで初期化
BattleManager* BattleManager::battleManagerInstance = nullptr;

BattleManager::BattleManager()
{

}

BattleManager::~BattleManager()
{

}

void BattleManager::Init()
{
	if (battleManagerInstance != nullptr)
	{
		return;
	}
	battleManagerInstance = new BattleManager();
}

void BattleManager::Release()
{
	if (battleManagerInstance != nullptr)
	{
		delete battleManagerInstance;
		battleManagerInstance = nullptr;
	}
}

void BattleManager::Update()
{

}

void BattleManager::Draw()
{

}

BattleManager* BattleManager::GetBattleManagerInstance()
{
	return battleManagerInstance;
}
