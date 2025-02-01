// TitleScene class

#include "TitleScene.hpp"

TitleScene::TitleScene(const InitData& init)
	: IScene{init}
{
	Scene::SetBackground(ColorF{ 0.443, 0.463, 0.243 });
}

void TitleScene::update()
{
	startTransition.update(startButton.mouseOver());
	configTransition.update(configButton.mouseOver());
	exitTransition.update(exitButton.mouseOver());

	// マウスオーバー時、カーソルを変更
	if (startButton.mouseOver() || configButton.mouseOver() || exitButton.mouseOver())
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (startButton.leftClicked())
	{
		// セーブデータの読み込み
		csv.load(SAVE_DATA_FILE);

		// 進行度で分岐
		if (Parse<int32>(csv[1][0]) == 0)
		{
			// ノベルシーンへ
			changeScene(State::NOVEL, 0.5s);
		}
		else
		{
			// ゲームシーンへ
			changeScene(State::GAME, 0.5s);
		}
	}
	else if (configButton.leftClicked())
	{
		// ゲームオーバーシーンへ
		changeScene(State::OVER, 0.5s);
	}
	else if (exitButton.leftClicked())
	{
		// 終了
		System::Exit();
	}
}

void TitleScene::draw() const
{
	// タイトルの表示
	FontAsset(FONT_MAKINAS)(U"総統の世界復興計画")
		.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.0, 0.0, 0.2 },
		Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }),
		120, Vec2{ Scene::Center().x, 100}, ColorF(0.675, 0.196, 0.196));

	// スタートボタンの描画
	startButton.draw(ColorF{ 1.0, startTransition.value() }).drawFrame(2);
	FontAsset(FONT_MAKINAS)(U"PLAY").drawAt(startButton.center(), ColorF{ 0.25 });

	// コンフィグボタンの描画
	configButton.draw(ColorF{ 1.0, configTransition.value() }).drawFrame(2);
	FontAsset(FONT_MAKINAS)(U"CONFIG").drawAt(configButton.center(), ColorF{ 0.25 });

	// 終了ボタンの描画
	exitButton.draw(ColorF{ 1.0, exitTransition.value() }).drawFrame(2);
	FontAsset(FONT_MAKINAS)(U"EXIT").drawAt(exitButton.center(), ColorF{ 0.25 });
}
