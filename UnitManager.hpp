// UnitManager class

#pragma once

#include "UnitBase.hpp"
#include "Components.hpp"

class UnitManager
{
public:

	// 初期化処理
	static void Init();

	// 解放処理
	static void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

	// UI関連処理
	void DrawUI();

	// ユニットの生成処理
	void InstantiateUnit();

	// インスタンスのゲッター関数
	static UnitManager* GetUnitManagerInstance();

	// 現在のターンのゲッター関数
	Turn GetCurrentTurn() const;

	// 全ユニットの座標配列のゲッター関数
	Array<Point> GetAllUnitPositionArray() const;

	// 操作状態のゲッター
	bool GetUnitControll() const;

	// 操作状態のセッター
	void SetUnitControll(bool val);

private:

	// コンストラクタ
	UnitManager();

	// デストラクタ
	~UnitManager();

	// Glyph とエフェクトの関数を組み合わせてテキストを描画
	// 勢いよく出る描画
	void DrawTextForce(const Font& font, double fontSize, const String& text, const Vec2& pos, const ColorF& color, double t, double characterPerSec) const;

	// 上から降ってくる描画
	void DrawTextFall(const Font& font, double fontSize, const String& text, const Vec2& pos, const ColorF& color, double t, double characterPerSec) const;

	// シングルトンクラスのインスタンスのポインタ
	static UnitManager* battleManagerInstance;

	// 待機ボタンの設定
	const Rect WAIT_BUTTON = { Arg::bottomRight(SCREEN_WIDTH - 20, SCREEN_HEIGHT - 30),
		BUTTON_WIDTH, BUTTON_HEIGHT };
	Transition waitTransition = BUTTON_TRANSITION;

	// 攻撃ボタンの設定
	const Rect ATTACK_BUTTON = WAIT_BUTTON.movedBy(-BUTTON_OFFSET);
	Transition attackTransition = BUTTON_TRANSITION;

	// 現在ターンの表示座標
	static constexpr Vec2 currentTurnDisplayPosition{ 10,20 };

	// ユニット生成用タイルの列挙
	const enum class Portal
	{
		TILE_PORTAL_ALPHA = 10,
		TILE_PORTAL_BLACK,
		TILE_PORTAL_BLUE,
		TILE_PORTAL_FUHRER,
		TILE_PORTAL_GREEN,
		TILE_PORTAL_PINK,
		TILE_PORTAL_RED,
	};

	// フォント演出用のストップウォッチ
	Stopwatch stopwatch;

	// メッセージフォントの描画位置
	Vec2 fontPosition;

	// 現在のターン
	Turn currentTurn;

	// 自軍ユニットのインスタンス配列
	Array<UnitBase*> playerUnitInstanceArray;

	// 敵軍ユニットのインスタンス配列
	Array<UnitBase*> enemyUnitInstanceArray;

	// 全ユニットのインスタンス配列
	Array<UnitBase*> allUnitInstanceArray;

	// ユニットを操作中か
	bool unitControll;

	int32 movedUnitCount;
};
