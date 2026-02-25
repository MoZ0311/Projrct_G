// GameOverScene

#include "GameOverScene.hpp"

GameOverScene::GameOverScene(const InitData& init)
	:IScene{ init }
{

}

void GameOverScene::update()
{
	retryTransition.update(retryButton.mouseOver());
	exitTransition.update(exitButton.mouseOver());

	// マウスオーバー時、カーソルを変更
	if (retryButton.mouseOver() || exitButton.mouseOver())
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (retryButton.leftClicked())
	{
		// タイトルシーンへ
		changeScene(State::TITLE, CHANGE_DURARTION);
	}

	if (exitButton.leftClicked())
	{
		// 終了
		System::Exit();
	}
}

void GameOverScene::draw() const
{
	// グラデーション背景の描画
	DrawRadialGradientBackground(BACKGROUD_COLOR_FROM, BACKGROUD_COLOR_TO);

	// GAME OVERの表示
	FontAsset(FONT_MAKINAS)(U"GAME OVER")
		.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.0, 0.0, 0.2 },
		Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }),
		120, Vec2{ Scene::Center().x, 100}, GameOverScene::TITLE_FONT_COLOR);

	// リトライボタンの描画
	retryButton.draw(ColorF{1.0, retryTransition.value()}).drawFrame(2);
	FontAsset(FONT_MAKINAS)(U"がんばる").drawAt(retryButton.center(), BUTTON_FONT_COLOR);

	// 終了ボタンの描画
	exitButton.draw(ColorF{ 1.0, exitTransition.value() }).drawFrame(2);
	FontAsset(FONT_MAKINAS)(U"あきらめる").drawAt(exitButton.center(), BUTTON_FONT_COLOR);
}
