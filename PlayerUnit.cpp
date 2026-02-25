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
