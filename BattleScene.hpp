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

	// マップ表示用の 2D カメラ
	Camera2D camera;
};
