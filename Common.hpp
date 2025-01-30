// SceneManager用定義

#pragma once

enum class State
{
	TITLE,
	NOVEL,
	GAME,
	OVER,
};

using App = SceneManager<State>;
