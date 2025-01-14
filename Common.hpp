// SceneManager用定義

#pragma once

enum class State
{
	TITLE,
	GAME,
	OVER,
};

using App = SceneManager<State>;
