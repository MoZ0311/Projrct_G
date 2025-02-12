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

	// フォントの初期位置を設定
	fontPosition = Scene::Center().movedBy(-160, 0);

	unitControll = false;
	movedUnitCount = 0;
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
	if (KeyR.down())
	{
		currentTurn = PLAYER_TURN;
		// 自軍ユニットの行動回復処理
		for (int32 i = 0; i < playerUnitInstanceArray.size(); ++i)
		{
			playerUnitInstanceArray[i]->UnitActionRefresh();
		}

		// ストップウォッチのリスタート
		stopwatch.restart();
	}

	switch (currentTurn)
	{
	case PREPARATION:
		stopwatch.start();
		break;

	case PLAYER_TURN:

		movedUnitCount = 0;
		// 自軍ユニットの更新処理
		for (int32 i = 0; i < playerUnitInstanceArray.size(); ++i)
		{
			playerUnitInstanceArray[i]->Update();

			// 行動終了したユニットをカウント
			if (playerUnitInstanceArray[i]->GetHasMoved())
			{
				movedUnitCount++;
			}
		}

		// 自軍が全て行動したら、敵軍のターン
		if (movedUnitCount == playerUnitInstanceArray.size())
		{
			stopwatch.restart();

			// 行動回復処理
			for (int32 i = 0; i < enemyUnitInstanceArray.size(); ++i)
			{
				enemyUnitInstanceArray[i]->UnitActionRefresh();
			}
			currentTurn = ENEMY_TURN;
		}
		break;

	case ENEMY_TURN:

		movedUnitCount = 0;
		// 敵軍ユニットの更新処理
		for (int32 i = 0; i < enemyUnitInstanceArray.size(); ++i)
		{
			enemyUnitInstanceArray[i]->Update();

			// 行動終了したユニットをカウント
			if (enemyUnitInstanceArray[i]->GetHasMoved())
			{
				movedUnitCount++;
			}
		}

		// 敵軍が全て行動したら、自軍のターン
		if (movedUnitCount == enemyUnitInstanceArray.size())
		{
			stopwatch.restart();

			// 行動回復処理
			for (int32 i = 0; i < playerUnitInstanceArray.size(); ++i)
			{
				playerUnitInstanceArray[i]->UnitActionRefresh();
			}

			currentTurn = PLAYER_TURN;
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
}

void UnitManager::DrawUI()
{
	// ストップウォッチの経過を取得
	const double t = stopwatch.sF();

	switch (currentTurn)
	{
	case PREPARATION:

		// フォントの表示
		DrawTextForce(
			FontAsset(FONT_MAKINAS), 80,
			U"戦闘開始", fontPosition,
			ColorF{ 1.0, 0.0, 0.0 }, t, 0.25);

		// 表示演出が終わったら、上にスライド
		if (t > 1)
		{
			fontPosition.y -= Scene::DeltaTime() * 800;

			// フォントが見えなくなったら、プレイヤーターンへ
			if (fontPosition.y < -300)
			{
				// ストップウォッチのリスタート
				stopwatch.restart();
				currentTurn = PLAYER_TURN;
			}
		}
		break;

	case PLAYER_TURN:

		// フォントの表示
		DrawTextFall(
			FontAsset(FONT_MAKINAS), 24,
			U"PLAYER TURN", currentTurnDisplayPosition,
			ColorF{ 0.0, 0.0, 1.0 }, t, 0.04);
		break;

	case ENEMY_TURN:

		// フォントの表示
		DrawTextFall(
			FontAsset(FONT_MAKINAS), 24,
			U"ENEMY TURN", currentTurnDisplayPosition,
			ColorF{ 1.0, 0.0, 0.0 }, t, 0.04);
		break;

	default:
		break;
	}
}

void UnitManager::DrawTextForce(const Font& font, double fontSize, const String& text, const Vec2& pos, const ColorF& color, double t, double characterPerSec) const
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

void UnitManager::DrawTextFall(const Font& font, double fontSize, const String& text, const Vec2& pos, const ColorF& color, double t, double characterPerSec) const
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

		const Vec2 offSet{ 1.5, 1.5 };
		const double y = EaseInQuad(Saturate(1 - (t - targetTime) / 0.3)) * -20.0;
		const double a = Min((t - targetTime) / 0.3, 1.0);
		glyph.texture.scaled(scale).draw(penPos + glyph.getOffset(scale) + offSet + Vec2{ 0, y }, ColorF{ 0, a });
		glyph.texture.scaled(scale).draw(penPos + glyph.getOffset(scale) + Vec2{ 0, y }, ColorF{ color, a });

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

bool UnitManager::GetUnitControll() const
{
	return unitControll;
}

void UnitManager::SetUnitControll(bool val)
{
	unitControll = val;
}
