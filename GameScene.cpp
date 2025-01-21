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

	// ゲームモード設定
	isEditing = false;
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

		if (isEditing)
		{
			// Stage class の更新処理
			Stage::GetStageInstance()->Update();
		}
		else
		{
			// Player class の更新処理
			Player::GetPlayerInstance()->Update();
		}
	}

	if (isEditing)
	{
		// カメラを操作可能に
		camera.setParameters(Camera2DParameters::MouseOnly());

		// UI class の更新処理
		UI::GetUIInstance()->Update();
	}
	else
	{
		// カメラを操作不能に
		camera.setParameters(Camera2DParameters::NoControl());

		// カメラをプレイヤーに追従
		camera.setTargetCenter(Player::GetPlayerInstance()->GetPlayerPosition());
		camera.setTargetScale(1.5);
	}

	//debug
	ClearPrint();
	Print << isEditing;
	Print << camera.getCenter();

	if (KeyM.down())
	{
		if (!isEditing)
		{
			camera.setTargetCenter(Vec2{0, 105});
			camera.setTargetScale(0.85);
		}
		isEditing = !isEditing;
	}
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

	if (isEditing)
	{
		// UI class の描画処理
		UI::GetUIInstance()->Draw();

		// 2D カメラの UI を表示する
		camera.draw(Palette::Deepskyblue);
	}
}
