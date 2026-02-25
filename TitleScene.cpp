// TitleScene class

#include "TitleScene.hpp"

TitleScene::TitleScene(const InitData& init)
	: IScene{init}
{
	animationCount = 0;
	animationIndex = 0;

	// CSVファイルの読み込み
	csv.load(SAVE_DATA_FILE);
	if (!csv)
	{
		throw Error{ U"CSVファイルが読み込めません" };
	}
}

void TitleScene::update()
{
	startTransition.update(startButton.mouseOver());
	battleTransition.update(battleButton.mouseOver());
	exitTransition.update(exitButton.mouseOver());

	// マウスオーバー時、カーソルを変更
	if (startButton.mouseOver() || battleButton.mouseOver() || exitButton.mouseOver())
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (startButton.leftClicked())
	{
		// ゲームシーンへ
		changeScene(State::GAME, CHANGE_DURARTION);
	}
	else if (battleButton.leftClicked())
	{
		// ノベルシーンへ
		changeScene(State::NOVEL, CHANGE_DURARTION);
	}
	else if (exitButton.leftClicked())
	{
		// 終了
		System::Exit();
	}

	// タイトルアニメーションの更新
	animationCount += Scene::DeltaTime() * 2;
	animationIndex = static_cast<int32>(animationCount);
	// アニメーションのリセット
	if (animationIndex >= ANIMATION_ARRAY.size())
	{
		animationIndex = 0;
		animationCount = 0;
	}
}

void TitleScene::draw() const
{
	// グラデーション背景の描画
	DrawRadialGradientBackground(ColorF{ 0.443, 0.463, 0.243 }, ColorF{ 0.283, 0.303, 0.083 });
	
	// タイトルの表示
	FontAsset(FONT_MAKINAS)(U"総統の世界復興計画")
		.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.0, 0.0, 0.2 },
		Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }),
		120, Vec2{ Scene::Center().x, 150}, ColorF(0.675, 0.196, 0.196));

	// スタートボタンの描画
	startButton.draw(ColorF{ 1.0, startTransition.value() }).drawFrame(2);
	FontAsset(FONT_MAKINAS)(U"復興").drawAt(startButton.center(), ColorF{ 0.25 });

	// バトルボタンの描画
	battleButton.draw(ColorF{ 1.0, battleTransition.value() }).drawFrame(2);
	FontAsset(FONT_MAKINAS)(U"バトル").drawAt(battleButton.center(), ColorF{ 0.25 });

	// 終了ボタンの描画
	exitButton.draw(ColorF{ 1.0, exitTransition.value() }).drawFrame(2);
	FontAsset(FONT_MAKINAS)(U"やめる").drawAt(exitButton.center(), ColorF{ 0.25 });

	// プレイヤー描画
	ANIMATION_ARRAY[animationIndex].mirrored(true).scaled(1.5).drawAt(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 150);
}
