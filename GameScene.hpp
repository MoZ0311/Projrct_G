// GameScene class

#pragma once

#include "Common.hpp"

class GameScene : public App::Scene
{
public:

	// コンストラクタ
	GameScene(const InitData& init);

	// デストラクタ
	~GameScene();

	// 更新処理
	void update() override;

	// 描画処理
	void draw() const override;

	// エディット中かのゲッター関数
	bool GetIsEditing();

private:

	// カメラの表示範囲の絶対値
	const Vec2 CAMERA_RANGE{ 700, 140 };

	// マップ表示用の 2D カメラ
	Camera2D camera;

	// マップのエディット中か
	bool isEditing;
};
