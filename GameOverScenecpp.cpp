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
		changeScene(State::TITLE, 0.5s);
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
	DrawRadialGradientBackground(ColorF{ 0.5 }, ColorF{ 0.1 });

	// GAME OVERの表示
	FontAsset(FONT_MAKINAS)(U"GAME OVER")
		.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.0, 0.0, 0.2 },
		Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }),
		120, Vec2{ Scene::Center().x, 100}, ColorF(0.675, 0.196, 0.196));

	// リトライボタンの描画
	retryButton.draw(ColorF{1.0, retryTransition.value()}).drawFrame(2);
	FontAsset(FONT_MAKINAS)(U"がんばる").drawAt(retryButton.center(), ColorF{ 0.25 });

	// 終了ボタンの描画
	exitButton.draw(ColorF{ 1.0, exitTransition.value() }).drawFrame(2);
	FontAsset(FONT_MAKINAS)(U"あきらめる").drawAt(exitButton.center(), ColorF{ 0.25 });
}
