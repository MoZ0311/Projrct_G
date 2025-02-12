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

	// ゲームモードを変更できるかの判定処理
	bool CanGameModeChange() const;

	// エディット中かのゲッター関数
	bool GetIsEditing() const;

private:

	// Glyph とエフェクトの関数を組み合わせてテキストを描画
	void DrawText(const Font& font, double fontSize, const String& text, const Vec2& pos, const ColorF& color, double t, double characterPerSec) const;

	// ステータスをもとに、マップの称号を決定
	void SetMapTitle();

	// マップの称号
	String mapTitle;

	// 各ステータスのインデックス
	static constexpr int32 MOISTURE = 0;
	static constexpr int32 URBAN = 1;
	static constexpr int32 NATURE = 2;
	static constexpr int32 ROUGH = 3;

	// マップの総合ステータス
	Array<int32> mapStatusArray;

	// フォント演出用のストップウォッチ
	Stopwatch stopwatch;

	// マップ表示用の 2D カメラ
	Camera2D camera;

	// マップのエディット中か
	bool isEditing;

	// マップ名の表示座標
	Vec2 mapNamePosition;

	// マップステータスの表示座標
	Vec2 mapStatusPosition;

	// 停止中のカウント
	double idolCount;
};
