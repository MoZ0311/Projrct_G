// GameOverScene class

#pragma once

#include "Common.hpp"
#include "Components.hpp"

class GameOverScene : public App::Scene
{
public:

	// コンストラクタ
	GameOverScene(const InitData& init);

	// 更新処理
	void update() override;

	// 描画処理
	void draw() const override;

private:

	// リトライボタン
	Rect retryButton = { Arg::center = Scene::Center().movedBy(BUTTON_OFFSET),
		BUTTON_WIDTH, BUTTON_HEIGHT };
	Transition retryTransition = BUTTON_TRANSITION;

	// 終了ボタン
	Rect exitButton = retryButton.movedBy(BUTTON_OFFSET);
	Transition exitTransition = BUTTON_TRANSITION;
};
