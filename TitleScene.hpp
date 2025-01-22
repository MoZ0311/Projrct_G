// TitleScene class

#pragma once

#include "Common.hpp"
#include "Components.hpp"

class TitleScene : public App::Scene
{
public:

	// コンストラクタ
	TitleScene(const InitData& init);

	// 更新処理
	void update() override;

	// 描画処理
	void draw() const override;

private:

	// START ボタンの設定
	Rect startButton = { Arg::center = Scene::Center(),
		BUTTON_WIDTH, BUTTON_HEIGHT };
	Transition startTransition = BUTTON_TRANSITION;


	// CONFIG ボタンの設定
	Rect configButton = startButton.movedBy(BUTTON_OFFSET);
	Transition configTransition = BUTTON_TRANSITION;

	// EXIT ボタンの設定
	Rect exitButton = configButton.movedBy(BUTTON_OFFSET);
	Transition exitTransition = BUTTON_TRANSITION;
};
