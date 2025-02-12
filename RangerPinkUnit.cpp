// RangerPinkUnit class

#include "RangerPinkUnit.hpp"

void RangerPinkUnit::SetUnitParameter(Point index)
{
	unitIdolArray = {
		TextureAsset(RANGER_PINK_BASE), TextureAsset(RANGER_PINK_IDOL)
	};

	unitWalkArray = {
		TextureAsset(RANGER_PINK_BASE), TextureAsset(RANGER_PINK_WALK_01),
		TextureAsset(RANGER_PINK_WALK_02), TextureAsset(RANGER_PINK_WALK_01)
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
