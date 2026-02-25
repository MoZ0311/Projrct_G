// UnitBase class

#pragma once

#include "Constants.hpp"

class UnitBase
{
public:

	// コンストラクタ
	UnitBase();

	// デストラクタ
	virtual ~UnitBase();

	// 更新処理
	virtual void Update();

	// 描画処理
	virtual void Draw();

	// ユニットの各種パラメータ設定
	virtual void SetUnitParameter(Point point) = 0;

	// ターン開始時の状態初期化
	void SetUnitActionState(bool value);

	// 各マスまでの距離のゲッター関数
	Grid<int32> GetDistanceGrid() const;

	// グリッド位置のゲッター関数
	Point GetGridPosition() const;

	// 移動力のゲッター関数
	int32 GetMovePower() const;

	// 選択状態のゲッター関数
	bool GetIsSelected() const;

	// 移動終了のゲッター関数
	bool GetHasMoved() const;

	// 行動終了のゲッター関数
	bool GetFinishAction() const;

	// 行動終了のセッター関数
	void SetFinishAction(bool value);

protected:

	// 移動処理
	void UnitMove();

	// 経路の生成
	void MakePath(Point targetPoint);

	// queのリセット処理
	void ResetQue();

	// 移動範囲の算出
	void CalcurateDistanceGrid();

	// 上、左、右、下のマスへのオフセット
	static constexpr Point OFFSETS[4] = { Point{ 0, -1 }, Point{ -1, 0 }, Point{ 1, 0 }, Point{ 0, 1 } };

	// ユニットの大きさ
	static constexpr double unitScale = 0.45;

	// 探索経路を格納する二重終端キュー
	std::deque<Point> q;

	// 始点位置から各マスまでの距離を格納する二次元配列
	Grid<int32> distanceGrid;

	// 視点位置から選択マスまでの経路配列
	Array<Point> routePath;

	// グリッド位置
	Point gridPosition;

	// 描画位置
	Vec2 drawPosition;

	// アイドルモーションのテクスチャ配列
	Array<Texture> unitIdolArray;

	// 歩行モーションのテクスチャ配列
	Array<Texture> unitWalkArray;

	// ユニットの移動力
	int32 movePower;

	// ユニットが選択されたか
	bool isSelected;

	// ユニットは移動中か
	bool isMoving;

	// ユニットの移動は終わっているか
	bool hasMoved;

	// ユニットの行動は終わっているか
	bool finishAction;

	// 左右反転するか
	bool flipX;

	// アイドル状態か
	bool isIdol;

	// アニメーション再生速度
	double animationSpeed;

	// アニメーションカウント
	double animationCount;

	// ユニットの移動インターバル
	double moveIntervalCount;
};
