// GameScene class

#include "GameScene.hpp"

#include "Player.hpp"

GameScene::GameScene(const InitData& init)
	:IScene{ init }
{
	// Player class の生成
	Player::Init();

	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
}

GameScene::~GameScene()
{
	Player::Release();
}

void GameScene::update()
{
	Player::GetPlayerInstance()->Update();
}

void GameScene::draw() const
{
	Player::GetPlayerInstance()->Draw();
}
