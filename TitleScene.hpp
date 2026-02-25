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

	// アニメーション配列
	const Array<Texture> ANIMATION_ARRAY = {
		TextureAsset(PLAYER_BASE), TextureAsset(PLAYER_IDOL)
	};

	// 読み込み対象のCSVファイル
	CSV csv;

	// アニメーション用変数
	double animationCount;
	int32 animationIndex;

	// START ボタンの設定
	const Rect startButton = { Arg::center = Scene::Center().moveBy(BUTTON_OFFSET),
		BUTTON_WIDTH, BUTTON_HEIGHT };
	Transition startTransition = BUTTON_TRANSITION;

	// BATTLE ボタンの設定
	const Rect battleButton = startButton.movedBy(BUTTON_OFFSET);
	Transition battleTransition = BUTTON_TRANSITION;

	// EXIT ボタンの設定
	const Rect exitButton = battleButton.movedBy(BUTTON_OFFSET);
	Transition exitTransition = BUTTON_TRANSITION;
};
