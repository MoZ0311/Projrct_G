// RangerBlackUnit class

#include "RangerBlackUnit.hpp"

void RangerBlackUnit::SetUnitParameter(Point index)
{
	unitIdolArray = {
		TextureAsset(RANGER_BLACK_BASE), TextureAsset(RANGER_BLACK_IDOL)
	};

	unitWalkArray = {
		TextureAsset(RANGER_BLACK_BASE), TextureAsset(RANGER_BLACK_WALK_01),
		TextureAsset(RANGER_BLACK_WALK_02), TextureAsset(RANGER_BLACK_WALK_01)
	};

	gridPosition = index;
	movePower = 3;

	// マップの中央を基準に反転の設定
	double mapCenter = Math::Round(distanceGrid.height() / 2.0);
	if (gridPosition.y < mapCenter)
	{
		flipX = true;
	}
	if (gridPosition.y > mapCenter)
	{
		flipX = false;
	}
}
