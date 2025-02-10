// BattleScene class

#include "BattleScene.hpp"

#include "UnitManager.hpp"
#include "Battlefield.hpp"

BattleScene::BattleScene(const InitData& init)
	:IScene{ init }
{
	// Battlefield class の生成
	Battlefield::Init();

	// マップの読み込み処理
	Battlefield::GetBattlefieldInstance()->LoadMapData();

	// BattleManager class の生成
	UnitManager::Init();

	// ユニットの生成処理
	UnitManager::GetBattleManagerInstance()->InstantiateUnit();

	// カメラを操作不能に
	camera.setParameters(Camera2DParameters::NoControl());
}

BattleScene::~BattleScene()
{
	// Battlefield class の解放
	Battlefield::Release();

	// UnitManager class の解放
	UnitManager::Release();
}

void BattleScene::update()
{
	// カメラの初期位置を設定
	camera.setTargetCenter(Vec2{ 0, 220 });

	// カメラの倍率を設定
	camera.setTargetScale(1.15);

	// 2D カメラを更新する
	camera.update();

	{
		const auto tr = camera.createTransformer();

		// Battlefield class の更新処理
		Battlefield::GetBattlefieldInstance()->Update();
	}

	// UI class の更新処理
	//UI::GetUIInstance()->Update();

	// UnitManager の更新処理
	UnitManager::GetBattleManagerInstance()->Update();

	// debug
	if (KeySpace.down())
	{
		changeScene(State::GAME, 0.5s);
	}
}

void BattleScene::draw() const
{
	// グラデーション背景の描画
	DrawVerticalGradientBackground(ColorF{ 0.0 }, ColorF{ 0.502, 0.0, 0.0 });

	{
		const auto tr = camera.createTransformer();

		// Battlefield class の描画処理
		Battlefield::GetBattlefieldInstance()->Draw();

		// UnitManager class の描画処理
		UnitManager::GetBattleManagerInstance()->Draw();
	}

	// UI class の描画処理
	//UI::GetUIInstance()->Draw();

	// 2D カメラの UI を表示する
	camera.draw(Palette::Deepskyblue);
}

void BattleScene::drawFadeIn(double t) const
{
	draw();
	const double r = Scene::Center().length();
	Circle(Scene::Center(), r).drawPie(0_deg, -(1.0 - t) * 360_deg);
}
