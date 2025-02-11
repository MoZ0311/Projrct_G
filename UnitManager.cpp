// UnitManager class

#include "UnitManager.hpp"
#include "Battlefield.hpp"
#include "PlayerUnit.hpp"
#include "RangerAlphaUnit.hpp"
#include "RangerBlackUnit.hpp"
#include "RangerBlueUnit.hpp"
#include "RangerGreenUnit.hpp"
#include "RangerPinkUnit.hpp"
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

	// ストップウォッチ設定
	stopwatch.reset();
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
		stopwatch.start();
		break;

	case PLAYER_TURN:
		// 自軍ユニットの更新処理
		for (int32 i = 0; i < playerUnitInstanceArray.size(); ++i)
		{
			playerUnitInstanceArray[i]->Update();
		}
		break;

	case ENEMY_TURN:
		// 敵軍ユニットの更新処理
		for (int32 i = 0; i < enemyUnitInstanceArray.size(); ++i)
		{
			enemyUnitInstanceArray[i]->Update();
		}
		break;

	default:
		break;
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

	if (currentTurn == PREPARATION)
	{
		// ストップウォッチの経過を取得
		const double t = stopwatch.sF();

		DrawText(
			FontAsset(FONT_MAKINAS), 80,
			U"戦闘開始", Vec2{ -160, SCREEN_HEIGHT / 2 - 80 },
			ColorF{ 1.0, 0.0, 0.0 }, t, 0.25);
	}
}

void UnitManager::DrawText(const Font& font, double fontSize, const String& text, const Vec2& pos, const ColorF& color, double t, double characterPerSec) const
{
	const double scale = (fontSize / font.fontSize());
	Vec2 penPos = pos;
	const ScopedCustomShader2D shader{ Font::GetPixelShader(font.method()) };
	ClearPrint();
	for (auto&& [i, glyph] : Indexed(font.getGlyphs(text)))
	{
		if (glyph.codePoint == U'\n')
		{
			penPos.x = pos.x;
			penPos.y += (font.height() * scale);
			continue;
		}

		const double targetTime = (i * characterPerSec);

		if (t < targetTime)
		{
			break;
		}

		const double s = Min((t - targetTime) / 0.1, 1.0);
		const double a = Min((t - targetTime) / 0.2, 1.0);

		const Vec2 offSet{ 3, 3 };
		glyph.texture.scaled(scale * (3.0 - s * 2)).draw((penPos + glyph.getOffset(scale) + offSet), ColorF{ 0, a });
		glyph.texture.scaled(scale * (3.0 - s * 2)).draw(penPos + glyph.getOffset(scale), ColorF{color, a});

		penPos.x += (glyph.xAdvance * scale);
	}
}

void UnitManager::InstantiateUnit()
{
	// マップのタイル配列を取得
	Grid<int32> tilegrid = Battlefield::GetBattlefieldInstance()->GetGrid();

	// グリッドの全ての要素を評価
	for (int32 row = 0; row < tilegrid.height(); ++row)
	{
		for (int32 column = 0; column < tilegrid.width(); ++column)
		{
			// タイルの種類をenum型で取得
			Portal portal = ToEnum<Portal>(tilegrid[row][column]);

			// ヘッダで定義したタイルの範囲であるなら、生成処理開始
			if (InRange(FromEnum(portal), FromEnum(Portal::TILE_PORTAL_ALPHA), FromEnum(Portal::TILE_PORTAL_RED)))
			{
				// ユニットのインスタンスを準備
				UnitBase* unitInstance = nullptr;

				if (portal == Portal::TILE_PORTAL_FUHRER)
				{
					// 総統のポータルマスなら、自軍を生成
					unitInstance = new PlayerUnit();

					// 生成したユニットを自軍用の配列に格納
					playerUnitInstanceArray.push_back(unitInstance);
				}
				else
				{
					// 他のポータルマスなら、敵軍を生成
					switch (portal)
					{
					case UnitManager::Portal::TILE_PORTAL_ALPHA:
						unitInstance = new RangerAlphaUnit();
						break;

					case UnitManager::Portal::TILE_PORTAL_BLACK:
						unitInstance = new RangerBlackUnit();
						break;

					case UnitManager::Portal::TILE_PORTAL_BLUE:
						unitInstance = new RangerBlueUnit();
						break;

					case UnitManager::Portal::TILE_PORTAL_GREEN:
						unitInstance = new RangerGreenUnit();
						break;

					case UnitManager::Portal::TILE_PORTAL_PINK:
						unitInstance = new RangerPinkUnit();
						break;

					case UnitManager::Portal::TILE_PORTAL_RED:
						unitInstance = new RangerRedUnit();
						break;

					default:
						break;
					}

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
