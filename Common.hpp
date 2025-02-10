// SceneManager用定義

#pragma once

#include "Constants.hpp"	// アセット、及び画面関連の定数をインクルード

enum class State
{
	TITLE,
	NOVEL,
	BATTLE,
	GAME,
	OVER,
};

/// @brief 放射状のグラデーションの背景を描画します。
/// @param centerColor 中心の色
/// @param outerColor 外周の色
void DrawRadialGradientBackground(const ColorF& centerColor, const ColorF& outerColor);

/// @brief 上下方向のグラデーションの背景を描画します。
/// @param topColor 上部の色
/// @param bottomColor 下部の色
void DrawVerticalGradientBackground(const ColorF& topColor, const ColorF& bottomColor);

using App = SceneManager<State>;
