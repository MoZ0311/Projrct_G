// BattleScene class

#include "BattleScene.hpp"

#include "Battlefield.hpp"
#include "UI.hpp"

BattleScene::BattleScene(const InitData& init)
	:IScene{ init }
{
	// Battlefield class の生成
	Battlefield::Init();

	// UI class の生成
	UI::Init();

	// 背景の色を設定する
	Scene::SetBackground(ColorF{ 0.69, 0.878, 0.902 });	
}

BattleScene::~BattleScene()
{
	// Battlefield class の解放
	Battlefield::Release();

	// UI class の解放
	UI::Release();
}

void BattleScene::update()
{
	// 2D カメラを更新する
	camera.update();

	{
		const auto tr = camera.createTransformer();

		// Battlefield class の更新処理
		Battlefield::GetBattlefieldInstance()->Update();
	}

	// UI class の更新処理
	UI::GetUIInstance()->Update();

	// debug
	if (KeySpace.down())
	{
		changeScene(State::GAME, 0.5s);
	}
}

void BattleScene::draw() const
{
	{
		const auto tr = camera.createTransformer();

		// Battlefield class の描画処理
		Battlefield::GetBattlefieldInstance()->Draw();

		// Player class の描画処理
		//Player::GetPlayerInstance()->Draw();
	}

	// UI class の描画処理
	UI::GetUIInstance()->Draw();

	// 2D カメラの UI を表示する
	camera.draw(Palette::Deepskyblue);
}

void BattleScene::drawFadeIn(double t) const
{
	draw();
	const double r = Scene::Center().length();
	Circle(Scene::Center(), r).drawPie(0_deg, -(1.0 - t) * 360_deg);
}
