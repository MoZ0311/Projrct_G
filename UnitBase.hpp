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

	// 移動処理
	void UnitMove(Point targetPoint);

	// queのリセット処理
	void ResetQue();

	// 移動範囲の算出
	Grid<int32> CreateDistanceGrid();

	// 経路を格納するque
	std::deque<Point> q;

	// 上、左、右、下のマスへのオフセット
	const Point OFFSETS[4] = { Point{ 0, -1 }, Point{ -1, 0 }, Point{ 1, 0 }, Point{ 0, 1 } };

	// ユニットの大きさ
	const double unitScale = 0.45;

	// 視点位置から各マスまでの距離を格納する二次元配列
	Grid<int32> distanceGrid;

	// 現在グリッド位置
	Point currentGridIndex;

	// 目標グリッド位置
	Point targetGridIndex;

	// 描画位置
	Vec2 drawPosition;

	// テクスチャ
	Texture unitTexture;

	// ユニットの移動力
	int32 movePower;
};
