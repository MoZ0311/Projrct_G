// NovelScene class

#include "NovelScene.hpp"

NovelScene::NovelScene(const InitData& init)
	:IScene{ init }
{

}

NovelScene::~NovelScene()
{

}

void NovelScene::update()
{

}

void NovelScene::draw() const
{
	MESSAGE_WINDOW.draw(ColorF{ 0, 0.8 }).drawFrame(5, 0, ColorF{ 0.8 });
}
