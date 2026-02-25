// NovelScene class

#pragma once

#include "Common.hpp"

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

	// フェードアウト
	void drawFadeOut(double t) const override;

private:

	// メッセージウィンドウの高さ
	static constexpr int32 WINDOW_HEIGHT = 152;

	// ウィンドウの枠の幅
	static constexpr int32 FRAME_THICKNESS = 5;

	// メッセージウィンドウの矩形
	static constexpr RoundRect MESSAGE_WINDOW{
		0, SCREEN_HEIGHT - WINDOW_HEIGHT,
		SCREEN_WIDTH, WINDOW_HEIGHT,
		10
	};

	// アイコンウィンドウの矩形
	static constexpr RoundRect ICON_WINDOW{
		FRAME_THICKNESS, SCREEN_HEIGHT - WINDOW_HEIGHT + FRAME_THICKNESS,
		WINDOW_HEIGHT - FRAME_THICKNESS * 2, WINDOW_HEIGHT - FRAME_THICKNESS * 2,
		5
	};

	// キャラアイコンの種類
	enum CharacterIcon
	{
		ICON_PLAYER,
		ICON_RED,
	};

	// 会話キャラの列
	static constexpr int32 CHARACTER_COLUMN = 0;

	// テキストの列
	static constexpr int32 TEXT_COLUMN = 1;

	// デフォルトのフォントサイズ
	static constexpr int32 FONT_SIZE = 40;

	// 読み込み対象のCSVファイル
	CSV csv;

	// 表示テキストのインデックス
	int32 textIndex;

	// アイコン画像
	Texture iconTexture;

	// 表示するメッセージテキスト
	String messageText;

	// 表示テキストの長さ
	double displayTextLength;

	// テキスト送りの速度
	double typeInterval;

	// 全文を表示し終えたか
	bool finishSentence;
};
