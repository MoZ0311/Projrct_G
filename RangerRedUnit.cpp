// RangerRedUnit class

#include "RangerRedUnit.hpp"

void RangerRedUnit::SetUnitParameter()
{
	unitIdolArray = {
		TextureAsset(RANGER_RED_BASE), TextureAsset(PLAYER_IDOL)
	};

	unitWalkArray = {
		TextureAsset(PLAYER_BASE), TextureAsset(PLAYER_WALK_01),
		TextureAsset(PLAYER_WALK_02), TextureAsset(PLAYER_WALK_01)
	};

	movePower = 4;
	flipX = true;
}
