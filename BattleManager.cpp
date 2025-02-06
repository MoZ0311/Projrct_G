// BattleManager class

#include "BattleManager.hpp"

// インスタンスをnullptrで初期化
BattleManager* BattleManager::battleManagerInstance = nullptr;

BattleManager::BattleManager()
{
	currentTurn = PREPARATION;
	unitBase = new UnitBase();
}

BattleManager::~BattleManager()
{
	delete unitBase;
	unitBase = nullptr;
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
	if (Key1.down())
	{
		currentTurn = PREPARATION;
	}

	if (Key2.down())
	{
		currentTurn = PLAYER_TURN;
	}

	if (Key3.down())
	{
		currentTurn = ENEMY_TURN;
	}

	unitBase->Update();
}

void BattleManager::Draw()
{
	ClearPrint();
	Print << Format(currentTurn);

	unitBase->Draw();
}

BattleManager* BattleManager::GetBattleManagerInstance()
{
	return battleManagerInstance;
}

Turn BattleManager::GetCurrentTurn() const
{
	return currentTurn;
}
