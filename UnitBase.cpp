// UnitBase class

#include "UnitBase.hpp"
#include "Battlefield.hpp"

UnitBase::UnitBase()
{
	unitScale = 0.45;
	unitTexture = TextureAsset(PLAYER_BASE);
	gridIndex = { 11, 11 };
	targetGridIndex = gridIndex;
	drawPosition = {};
	movePower = 4;
}

UnitBase::~UnitBase()
{

}

void UnitBase::Update()
{
	drawPosition = Battlefield::GetBattlefieldInstance()->ToTileBottomCenter(gridIndex, 12);

	if (targetGridIndex != gridIndex)
	{
		// 移動処理
		UnitMove(targetGridIndex);
	}

	// debug
	if (KeyQ.down())
	{
		targetGridIndex = { 8, 10 };
	}
	if (MouseR.down())
	{
		CreateMoveRangeGrid();
	}
}

void UnitBase::Draw()
{
	unitTexture.scaled(unitScale).draw(Arg::bottomCenter = drawPosition
		.moveBy(0, -Battlefield::GetBattlefieldInstance()->TILE_THICKNESS - Battlefield::GetBattlefieldInstance()->TILE_OFFSET.y / 2));

	//ClearPrint();
	//Print << CreateMoveRangeGrid();
}

void UnitBase::UnitMove(Point targetPoint)
{
	gridIndex = targetPoint;
}

Grid<int32> UnitBase::CreateMoveRangeGrid()
{
	// 移動範囲の空の二次元配列
	Grid<Point> mapGrid(Size{ movePower * 2 + 1, movePower * 2 + 1 });

	// 移動可能範囲の中央を現在のインデックスに
	mapGrid[movePower][movePower] = gridIndex;	

	// ユニット周辺の二次元配列を設定
	for (int32 y = 0; y < movePower; ++y)
	{
		for (int32 x = 0; x < movePower - y + 1; x++)
		{
			mapGrid[movePower - x][movePower - y] = Point{ gridIndex.x - x, gridIndex.y - y };
		}

	}
	for (int32 x = 0; x < movePower; ++x)
	{
		for (int32 y = 0; y < movePower - x + 1; y++)
		{
			mapGrid[movePower + x][movePower - y] = Point{ gridIndex.x + x, gridIndex.y - y };
		}
	}
	for (int32 y = 0; y < movePower; ++y)
	{
		for (int32 x = 0; x < movePower - y + 1; x++)
		{
			mapGrid[movePower + x][movePower + y] = Point{ gridIndex.x + x, gridIndex.y + y };
		}
	}
	for (int32 x = 0; x < movePower; ++x)
	{
		for (int32 y = 0; y < movePower - x + 1; y++)
		{
			mapGrid[movePower - x][movePower + y] = Point{ gridIndex.x - x, gridIndex.y + y };
		}
	}

	// マス目に応じた残り移動力の二次元配列
	Grid<int32> moveRemainGrid(mapGrid.size(), -1);
	for (int32 x = 0; x < moveRemainGrid.width(); x++)
	{
		for (int32 y = 0; y < moveRemainGrid.height(); y++)
		{
			if (mapGrid[x][y] == Point{ 0, 0 })
			{
				moveRemainGrid[x][y] = -1;
			}
			else
			{
				moveRemainGrid[x][y] = 0;
			}
		}
	}
	moveRemainGrid[movePower][movePower] = movePower;

	// 周辺地形の移動コストの二次元配列

	return moveRemainGrid;
}
