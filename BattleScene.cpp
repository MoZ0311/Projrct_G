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
	if (KeySpace.down())
	{
		changeScene(State::GAME, 0.5s);
	}
}

void BattleScene::draw() const
{

}

void BattleScene::drawFadeIn(double t) const
{
	draw();
	const double r = Scene::Center().length();
	Circle(Scene::Center(), r).drawPie(0_deg, -(1.0 - t) * 360_deg);
}
