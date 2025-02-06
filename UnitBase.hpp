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

	// ユニットの大きさ
	double unitScale;

	// テクスチャ
	Texture unitTexture;

	// グリッド位置
	Point gridIndex;

	// 描画位置
	Vec2 drawPosition;
};
