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
	movePower = 3;
	flipX = true;
}
