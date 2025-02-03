// BattleScene class

#include "BattleScene.hpp"

BattleScene::BattleScene(const InitData& init)
	:IScene{ init }
{
	Scene::SetBackground(ColorF{ 0.69, 0.878, 0.902 });
}

BattleScene::~BattleScene()
{

}

void BattleScene::update()
{

}

void BattleScene::draw() const
{

}
