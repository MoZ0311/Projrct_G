// PlayerUnit class

#include "PlayerUnit.hpp"

void PlayerUnit::SetUnitParameter(Point index)
{
	unitIdolArray = {
		TextureAsset(PLAYER_BASE), TextureAsset(PLAYER_IDOL)
	};

	unitWalkArray = {
		TextureAsset(PLAYER_BASE), TextureAsset(PLAYER_WALK_01),
		TextureAsset(PLAYER_WALK_02), TextureAsset(PLAYER_WALK_01)
	};

	gridIndex = index;
	movePower = 4;
}
