// 各シーンでの汎用関数

#include "Common.hpp"

void DrawRadialGradientBackground(const ColorF& centerColor, const ColorF& outerColor)
{
	Circle{ Scene::Center(), (Scene::Size().length() * 0.5) }
	.draw(centerColor, outerColor);
}

void DrawVerticalGradientBackground(const ColorF& topColor, const ColorF& bottomColor)
{
	Scene::Rect()
		.draw(Arg::top = topColor, Arg::bottom = bottomColor);
}
