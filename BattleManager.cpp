// BattleManager class

#include "BattleManager.hpp"
#include "PlayerUnit.hpp"
#include "RangerRedUnit.hpp"

// インスタンスをnullptrで初期化
BattleManager* BattleManager::battleManagerInstance = nullptr;

BattleManager::BattleManager()
{
	currentTurn = PREPARATION;

	// 両軍のユニット配列を初期化
	playerUnitInstanceArray = {};
	enemyUnitInstanceArray = {};
}

BattleManager::~BattleManager()
{
	// 自軍ユニットを全て解放
	for (int32 i = 0; i < playerUnitInstanceArray.size(); ++i)
	{
		delete playerUnitInstanceArray[i];
		playerUnitInstanceArray[i] = nullptr;
	}

	// 敵軍ユニットを全て解放
	for (int32 i = 0; i < enemyUnitInstanceArray.size(); ++i)
	{
		delete enemyUnitInstanceArray[i];
		enemyUnitInstanceArray[i] = nullptr;
	}

	// 両軍のユニット配列をクリア
	playerUnitInstanceArray.clear();
	enemyUnitInstanceArray.clear();
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

	switch (currentTurn)
	{
	case PREPARATION:
		break;

	case PLAYER_TURN:
		break;

	case ENEMY_TURN:
		break;

	default:
		break;
	}

	// 自軍ユニットの更新処理
	for (int32 i = 0; i < playerUnitInstanceArray.size(); ++i)
	{
		playerUnitInstanceArray[i]->Update();
	}

	// 敵軍ユニットを全て解放
	for (int32 i = 0; i < enemyUnitInstanceArray.size(); ++i)
	{
		enemyUnitInstanceArray[i]->Update();
	}
}

void BattleManager::Draw()
{
	// 自軍ユニットの描画処理
	for (int32 i = 0; i < playerUnitInstanceArray.size(); ++i)
	{
		playerUnitInstanceArray[i]->Draw();
	}

	// 敵軍ユニットを全て解放
	for (int32 i = 0; i < enemyUnitInstanceArray.size(); ++i)
	{
		enemyUnitInstanceArray[i]->Draw();
	}
}

BattleManager* BattleManager::GetBattleManagerInstance()
{
	return battleManagerInstance;
}

Turn BattleManager::GetCurrentTurn() const
{
	return currentTurn;
}
