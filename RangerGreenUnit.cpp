// RangerGreenUnit class

#include "RangerGreenUnit.hpp"

void RangerGreenUnit::SetUnitParameter(Point index)
{
	unitIdolArray = {
		TextureAsset(RANGER_GREEN_BASE), TextureAsset(RANGER_GREEN_IDOL)
	};

	unitWalkArray = {
		TextureAsset(RANGER_GREEN_BASE), TextureAsset(RANGER_GREEN_WALK_01),
		TextureAsset(RANGER_GREEN_WALK_02), TextureAsset(RANGER_GREEN_WALK_01)
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
