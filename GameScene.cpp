// GameScene class

#include "GameScene.hpp"

#include "Player.hpp"
#include "Stage.hpp"

GameScene::GameScene(const InitData& init)
	:IScene{ init }
{
	// Stage class の生成
	Stage::Init();

	// Player class の生成
	Player::Init();

	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
}

GameScene::~GameScene()
{
	// Stage class の解放
	Stage::Release();

	// Player class の解放
	Player::Release();
}

void GameScene::update()
{
	// Stage class の更新処理
	Stage::GetStageInstance()->Update();

	// Player class の更新処理
	Player::GetPlayerInstance()->Update();
}

void GameScene::draw() const
{
	// Stage class の描画処理
	Stage::GetStageInstance()->Draw();

	// Player class の描画処理
	Player::GetPlayerInstance()->Draw();
}
