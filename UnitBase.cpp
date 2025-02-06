// UnitBase class

#include "UnitBase.hpp"
#include "Battlefield.hpp"

UnitBase::UnitBase()
{
	unitScale = 0.45;
	unitTexture = TextureAsset(PLAYER_BASE);
	gridIndex = { 11, 11 };
	drawPosition = {};
}

UnitBase::~UnitBase()
{

}

void UnitBase::Update()
{
	drawPosition = Battlefield::GetBattlefieldInstance()->ToTileBottomCenter(gridIndex, 12);
}

void UnitBase::Draw()
{
	unitTexture.scaled(unitScale).draw(Arg::bottomCenter = drawPosition
		.moveBy(0, -Battlefield::GetBattlefieldInstance()->TILE_THICKNESS - Battlefield::GetBattlefieldInstance()->TILE_OFFSET.y / 2));

	ClearPrint();
	Print << gridIndex;
}
