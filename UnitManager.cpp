// UnitManager class

#include "UnitManager.hpp"
#include "Battlefield.hpp"
#include "PlayerUnit.hpp"
#include "RangerRedUnit.hpp"

// インスタンスをnullptrで初期化
UnitManager* UnitManager::battleManagerInstance = nullptr;

UnitManager::UnitManager()
{
	currentTurn = PREPARATION;

	// 両軍のユニット配列を初期化
	playerUnitInstanceArray = {};
	enemyUnitInstanceArray = {};

	// 全ユニットの配列を初期化
	allUnitInstanceArray = {};
}

UnitManager::~UnitManager()
{
	// 両軍のユニット配列をクリア
	playerUnitInstanceArray.clear();
	enemyUnitInstanceArray.clear();

	// 全ユニットのインスタンスを削除
	for (int32 i = 0; i < allUnitInstanceArray.size(); ++i)
	{
		delete allUnitInstanceArray[i];
		allUnitInstanceArray[i] = nullptr;
	}

	// 配列をクリア
	allUnitInstanceArray.clear();
}

void UnitManager::Init()
{
	if (battleManagerInstance != nullptr)
	{
		return;
	}
	battleManagerInstance = new UnitManager();
}

void UnitManager::Release()
{
	if (battleManagerInstance != nullptr)
	{
		delete battleManagerInstance;
		battleManagerInstance = nullptr;
	}
}

void UnitManager::Update()
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

	// 敵軍ユニットの更新処理
	for (int32 i = 0; i < enemyUnitInstanceArray.size(); ++i)
	{
		enemyUnitInstanceArray[i]->Update();
	}

	// 全ユニットのソート処理
	// 比較関数を用いて、原点からグリッド座標までのマンハッタン距離でソート
	allUnitInstanceArray.sort_by([](const UnitBase* a, const UnitBase* b)
		{ return (a->GetGridPosition().manhattanLength() < b->GetGridPosition().manhattanLength()); });
	
}

void UnitManager::Draw()
{
	// 選択ユニットの移動範囲の描画
	for (int32 i = 0; i < allUnitInstanceArray.size(); ++i)
	{
		if (allUnitInstanceArray[i]->GetIsSelected())
		{
			// ユニットから各パラメータを取得
			Grid<int32> distanceGrid = allUnitInstanceArray[i]->GetDistanceGrid();
			int32 movePower = allUnitInstanceArray[i]->GetMovePower();

			// Battlefield class に描画させる
			Battlefield::GetBattlefieldInstance()->DrawMoveRange(distanceGrid, movePower);
		}
	}

	// 全ユニットの描画処理
	for (int32 i = 0; i < allUnitInstanceArray.size(); ++i)
	{
		allUnitInstanceArray[i]->Draw();
	}
}

void UnitManager::InstantiateUnit()
{
	// マップのタイル配列を取得
	Grid<int32> tilegrid = Battlefield::GetBattlefieldInstance()->GetGrid();

	constexpr int32 TILE_PORTAL_BLUE = 12;
	constexpr int32 TILE_PORTAL_RED = 13;

	// グリッドの全ての要素を評価
	for (int32 row = 0; row < tilegrid.height(); ++row)
	{
		for (int32 column = 0; column < tilegrid.width(); ++column)
		{
			if (tilegrid[row][column] == TILE_PORTAL_BLUE ||
				tilegrid[row][column] == TILE_PORTAL_RED)
			{
				// ユニットのインスタンスを準備
				UnitBase* unitInstance = nullptr;

				// 青のポータルマスなら、自軍を生成
				if (tilegrid[row][column] == TILE_PORTAL_BLUE)
				{
					unitInstance = new PlayerUnit();

					// 生成したユニットを自軍用の配列に格納
					playerUnitInstanceArray.push_back(unitInstance);
				}

				// 赤のポータルマスなら、敵軍を生成
				if (tilegrid[row][column] == TILE_PORTAL_RED)
				{
					unitInstance = new RangerRedUnit();

					// 生成したユニットを敵軍用の配列に格納
					enemyUnitInstanceArray.push_back(unitInstance);
				}

				// 生成したユニットを共用配列に格納
				allUnitInstanceArray.push_back(unitInstance);

				// 生成したユニットにグリッド座標を与える
				unitInstance->SetUnitParameter(Point{ column, row });
			}
		}
	}
}

UnitManager* UnitManager::GetUnitManagerInstance()
{
	return battleManagerInstance;
}

Turn UnitManager::GetCurrentTurn() const
{
	return currentTurn;
}

Array<Point> UnitManager::GetAllUnitPositionArray() const
{
	// 空の配列を用意
	Array<Point> unitPositionArray{};

	// すべてのユニットのグリッド位置を順番に格納
	for (int32 i = 0; i < allUnitInstanceArray.size(); ++i)
	{
		Point unitPosition = allUnitInstanceArray[i]->GetGridPosition();
		unitPositionArray.push_back(unitPosition);
	}

	return unitPositionArray;
}
