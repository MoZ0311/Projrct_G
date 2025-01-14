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

	Rect startButton = buttonBase;
	Transition startTransition = buttonTransition;

	Rect configButton = startButton.movedBy(0, 100);
	Transition configTransition = buttonTransition;

	Rect exitButton = configButton.movedBy(0, 100);
	Transition exitTransition = buttonTransition;
};
