// BattleScene class

#pragma once

#include "Common.hpp"

class BattleScene : public App::Scene
{
public:

	// コンストラクタ
	BattleScene(const InitData& init);

	// デストラクタ
	~BattleScene();

	// 更新処理
	void update() override;

	// 描画処理
	void draw() const override;

	// フェードイン
	void drawFadeIn(double t) const override;

private:

	// カメラの目標位置
	static constexpr Vec2 CAMERA_POSITION{ 0, 232 };

	// カメラの倍率
	static constexpr double CAMERA_SCALE = 1.05;

	// 背景のグラデーション先
	static constexpr ColorF BACKGROUD_COLOR_TO{ 0.502, 0.0, 0.0 };

	// マップ表示用の 2D カメラ
	Camera2D camera;
};
