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

	// 移動範囲の算出
	Grid<int32> CreateMoveRangeGrid();

	// ユニットの大きさ
	double unitScale;

	// テクスチャ
	Texture unitTexture;

	// グリッド位置
	Point gridIndex;

	// 目標グリッド位置
	Point targetGridIndex;

	// 描画位置
	Vec2 drawPosition;

	// ユニットの移動力
	int32 movePower;

	// 移動可能グリッドの配列
	//Grid<int32> moveRangeGrid;
};
