// UIコンポーネント定義

#pragma once

constexpr int32 BUTTON_WIDTH = 300;		// ボタンの幅
constexpr int32 BUTTON_HEIGHT = 60;		// ボタンの高さ

constexpr Rect buttonBase{ BUTTON_WIDTH, BUTTON_HEIGHT };

constexpr Transition buttonTransition{ 0.4s, 0.2s };	// トランジション
