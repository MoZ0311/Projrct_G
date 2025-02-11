// RangerRedUnit class

#include "RangerRedUnit.hpp"

void RangerRedUnit::SetUnitParameter(Point index)
{
	unitIdolArray = {
		TextureAsset(RANGER_RED_BASE), TextureAsset(RANGER_RED_IDOL)
	};

	unitWalkArray = {
		TextureAsset(RANGER_RED_BASE), TextureAsset(RANGER_RED_WALK_01),
		TextureAsset(RANGER_RED_WALK_02), TextureAsset(RANGER_RED_WALK_01)
	};

	gridPosition = index;
	movePower = 4;

	// マップの中央を基準に反転の設定
	double mapCenter = Math::Round((distanceGrid.height()) / 2.0);
	if (gridPosition.y < mapCenter)
	{
		flipX = true;
	}
	if (gridPosition.y > mapCenter)
	{
		flipX = false;
	}
}
