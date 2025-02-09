// UnitBase class

#pragma once

#include "Constants.hpp"

class UnitBase
{
public:

	// コンストラクタ
	UnitBase();

	// デストラクタ
	~UnitBase();

	// 更新処理
	virtual void Update();

	// 描画処理
	virtual void Draw();

protected:

	// ユニットの各種パラメータ設定
	virtual void SetUnitParameter();

	// 移動処理
	void UnitMove();

	// 経路の生成
	void MakePath(Point targetPoint);

	// queのリセット処理
	void ResetQue();

	// 移動範囲の算出
	void CalcurateDistanceGrid();

	// 上、左、右、下のマスへのオフセット
	const Point OFFSETS[4] = { Point{ 0, -1 }, Point{ -1, 0 }, Point{ 1, 0 }, Point{ 0, 1 } };

	// ユニットの大きさ
	const double unitScale = 0.45;

	// 探索経路を格納する二重終端キュー
	std::deque<Point> q;

	// 始点位置から各マスまでの距離を格納する二次元配列
	Grid<int32> distanceGrid;

	// 視点位置から選択マスまでの経路配列
	Array<Point> routePath;

	// グリッド位置
	Point gridIndex;

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
