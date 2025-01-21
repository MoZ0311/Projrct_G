// GameScene class

#include "GameScene.hpp"

#include "Player.hpp"
#include "Stage.hpp"
#include "UI.hpp"

GameScene::GameScene(const InitData& init)
	:IScene{ init }
{
	// Stage class の生成
	Stage::Init();

	// Player class の生成
	Player::Init();

	// UI class の生成
	UI::Init();

	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	// カメラの倍率を設定
	camera.setTargetScale(1.5);
}

GameScene::~GameScene()
{
	// Stage class の解放
	Stage::Release();

	// Player class の解放
	Player::Release();

	// UI class の解放
	UI::Release();
}

void GameScene::update()
{
	// 2D カメラを更新する
	camera.update();

	{
		const auto tr = camera.createTransformer();

		// Stage class の更新処理
		Stage::GetStageInstance()->Update();

		// Player class の更新処理
		Player::GetPlayerInstance()->Update();
	}

	// カメラをプレイヤーに追従
	camera.setTargetCenter(Player::GetPlayerInstance()->GetPlayerPosition());

	// UI class の更新処理
	UI::GetUIInstance()->Update();
}

void GameScene::draw() const
{
	{
		const auto tr = camera.createTransformer();

		// Stage class の描画処理
		Stage::GetStageInstance()->Draw();

		// Player class の描画処理
		Player::GetPlayerInstance()->Draw();
	}

	// UI class の描画処理
	UI::GetUIInstance()->Draw();

	// 2D カメラの UI を表示する
	camera.draw(Palette::Deepskyblue);
}
