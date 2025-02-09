// UnitBase class

#include "UnitBase.hpp"
#include "Battlefield.hpp"

UnitBase::UnitBase()
{
	unitTexture = TextureAsset(PLAYER_BASE);
	currentGridIndex = { 11, 11 };
	targetGridIndex = currentGridIndex;
	drawPosition = {};
	movePower = 4;
	distanceGrid = { Battlefield::GetBattlefieldInstance()->GetGrid().size(), INF };
	ResetQue();
}

UnitBase::~UnitBase()
{

}

void UnitBase::Update()
{
	drawPosition = Battlefield::GetBattlefieldInstance()->ToTileBottomCenter(currentGridIndex, 12);

	if (targetGridIndex != currentGridIndex)
	{
		// 移動処理
		UnitMove(targetGridIndex);
	}

	// debug
	if (KeyQ.down())
	{
		targetGridIndex = { 8, 10 };
	}
}

void UnitBase::Draw()
{
	unitTexture.scaled(unitScale).draw(Arg::bottomCenter = drawPosition
		.moveBy(0, -Battlefield::GetBattlefieldInstance()->TILE_THICKNESS - Battlefield::GetBattlefieldInstance()->TILE_OFFSET.y / 2));

	//debug
	ClearPrint();
	Print << CreateDistanceGrid();
}

void UnitBase::UnitMove(Point targetPoint)
{
	currentGridIndex = targetPoint;
	// 初期位置の設定
	ResetQue();
}

void UnitBase::ResetQue()
{
	// 経路をリセットし、現在位置を再設定
	q.clear();
	q.push_back(currentGridIndex);

	// 距離の二次元配列を再計算
	distanceGrid.fill(INF);
	distanceGrid[currentGridIndex] = 0;
}

Grid<int32> UnitBase::CreateDistanceGrid()
{
	// 幅優先探索
	if (!q.empty())
	{
		const Point currentPos = q.front();
		q.pop_front();
		const int32 currentDistance = distanceGrid[currentPos];

		// 範囲for文で、OFFSETSを要素の数だけ順に代入
		for (const auto& offset : OFFSETS)
		{
			// 次の探索目標を設定
			const Point nextPosition = (currentPos + offset);

			// 範囲外アクセスを防ぐcontinue
			if (!(nextPosition.x < distanceGrid.width() && nextPosition.y < distanceGrid.height()))
			{
				continue;
			}

			// 探索したマスを格納
			if (Battlefield::GetBattlefieldInstance()->GetCanEnterGrid()[nextPosition] &&
				currentDistance + 1 < distanceGrid[nextPosition])
			{
				distanceGrid[nextPosition] = (currentDistance + 1);
				q.push_back(nextPosition);
			}
		}
	}
	return distanceGrid;
}
