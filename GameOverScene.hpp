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
	Rect retryButton = { Arg::center = Scene::Center().movedBy(0, 100),
		BUTTON_WIDTH, BUTTON_HEIGHT };
	Transition retryTransition = buttonTransition;

	// 終了ボタン
	Rect exitButton = retryButton.movedBy(0, 100);
	Transition exitTransition = buttonTransition;
	
};
