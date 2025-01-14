// GameScene class

#include "GameScene.hpp"

#include "Player.hpp"
#include "Stage.hpp"

GameScene::GameScene(const InitData& init)
	:IScene{ init }
{
	// Player class の生成
	Player::Init();

	// Stage class の生成
	Stage::Init();

	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
}

GameScene::~GameScene()
{
	// Player class の解放
	Player::Release();

	// Stage class の解放
	Stage::Release();
}

void GameScene::update()
{
	// Player class の更新処理
	Player::GetPlayerInstance()->Update();

	// Stage class の更新処理
	Stage::GetStageInstance()->Update();
}

void GameScene::draw() const
{
	// Player class の描画処理
	Player::GetPlayerInstance()->Draw();

	// Stage class の描画処理
	Stage::GetStageInstance()->Draw();
}
