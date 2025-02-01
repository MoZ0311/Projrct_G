// NovelScene class

#include "NovelScene.hpp"

NovelScene::NovelScene(const InitData& init)
	:IScene{ init }
{
	iconTexture = TextureAsset(U"PlayerBase");
	messageText = U"あああああああああああああ";
	textIndex = 0;
	typeInterval = 0.1;
}

NovelScene::~NovelScene()
{

}

void NovelScene::update()
{
	textIndex += 1 / typeInterval * Scene::DeltaTime();
}

void NovelScene::draw() const
{
	// メッセージウィンドウの描画
	MESSAGE_WINDOW.draw(ColorF{ 0, 0.8 }).drawFrame(FRAME_THICKNESS, 0, ColorF{ 0.8 });
	FontAsset(U"MAKINAS")(messageText.substr(0, static_cast<size_t>(textIndex))).draw(40, ICON_WINDOW.w + FRAME_THICKNESS * 2 + 20, ICON_WINDOW.y);

	// アイコンの描画
	ICON_WINDOW.draw(ColorF{ 0.5 }).drawFrame(0, FRAME_THICKNESS, ColorF{ 0.8 });
	ICON_WINDOW(iconTexture(16, 0, 96, 96)).draw();
}
