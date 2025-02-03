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

using App = SceneManager<State>;
