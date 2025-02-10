// PlayerUnit class

#include "PlayerUnit.hpp"

void PlayerUnit::SetUnitParameter()
{
	unitIdolArray = {
		TextureAsset(PLAYER_BASE), TextureAsset(PLAYER_IDOL)
	};

	unitWalkArray = {
		TextureAsset(PLAYER_BASE), TextureAsset(PLAYER_WALK_01),
		TextureAsset(PLAYER_WALK_02), TextureAsset(PLAYER_WALK_01)
	};

	movePower = 4;
}
