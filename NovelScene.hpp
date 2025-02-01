// NovelScene class

#pragma once

#include "Common.hpp"
#include "Constants.hpp"

class NovelScene : public App::Scene
{
public:

	// コンストラクタ
	NovelScene(const InitData& init);

	// デストラクタ
	~NovelScene();

	// 更新処理
	void update() override;

	// 描画処理
	void draw() const override;

private:

	// メッセージウィンドウの高さ
	const int32 WINDOW_HEIGHT = 150;

	// ウィンドウの枠の幅
	const int32 FRAME_THICKNESS = 5;

	// メッセージウィンドウの矩形
	const RoundRect MESSAGE_WINDOW{
		0, SCREEN_HEIGHT - WINDOW_HEIGHT,
		SCREEN_WIDTH, WINDOW_HEIGHT,
		10
	};

	// アイコンウィンドウの矩形
	const RoundRect ICON_WINDOW{
		FRAME_THICKNESS, MESSAGE_WINDOW.y + FRAME_THICKNESS,
		WINDOW_HEIGHT - FRAME_THICKNESS * 2, WINDOW_HEIGHT - FRAME_THICKNESS * 2,
		5
	};

	// アイコン画像
	Texture iconTexture;

	// 表示するメッセージテキスト
	String messageText;

	// テキストのインデックス
	double textIndex;

	// テキスト送りの速度
	double typeInterval;
};
