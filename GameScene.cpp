// GameScene class

#include "GameScene.hpp"

#include "Player.hpp"
#include "TownField.hpp"
#include "UI.hpp"

GameScene::GameScene(const InitData& init)
	:IScene{ init }
{
	// TownField class の生成
	TownField::Init(this);

	// Player class の生成
	Player::Init(this);

	// UI class の生成
	UI::Init();

	// 背景の色を設定する
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	// カメラの倍率を設定
	camera.setTargetScale(1.5);

	// ゲームモード設定
	isEditing = false;
}

GameScene::~GameScene()
{
	// TownField class の解放
	TownField::Release();

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
			// TownField class の更新処理
			TownField::GetTownFieldInstance()->Update();
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

	// ゲームモードの切り替え
	if (KeyF.down())
	{

		ClearPrint();
		if (CanGameModeChange())
		{
			if (!isEditing)
			{
				// エディットモードになる時、カメラを再設定
				camera.setTargetCenter(Vec2{ 0, 105 });
				camera.setTargetScale(0.85);
			}

			isEditing = !isEditing;
		}
		else
		{
			Print << U"セーブしろ!!!";
		}
	}

	// カメラリセット
	if (MouseM.down() && isEditing)
	{
		camera.setTargetCenter(Vec2{ 0, 105 });
		camera.setTargetScale(0.85);
	}
}

void GameScene::draw() const
{
	{
		const auto tr = camera.createTransformer();

		// TownField class の描画処理
		TownField::GetTownFieldInstance()->Draw();

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

bool GameScene::CanGameModeChange() const
{
	if (isEditing)
	{
		return TownField::GetTownFieldInstance()->MapEqualsCSV();
	}

	return true;
}

bool GameScene::GetIsEditing() const
{
	return isEditing;
}
