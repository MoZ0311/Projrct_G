// UnitBase class

#include "UnitBase.hpp"
#include "Battlefield.hpp"

UnitBase::UnitBase()
{
	SetUnitParameter();
	drawPosition = {};
	distanceGrid = { Battlefield::GetBattlefieldInstance()->GetGrid().size(), INF };
	routePath = {};
	isSelected = false;
	isMoving = false;
	flipX = false;
	isIdol = true;
	animationSpeed = 0;
	animationCount = 0;
	moveIntervalCount = 0;
	ResetQue();
}

UnitBase::~UnitBase()
{

}

void UnitBase::Update()
{
	// クリックによる各種処理
	if (!isMoving && MouseL.down())
	{
		// 前提として、移動中のクリックは受付けない
		if (Battlefield::GetBattlefieldInstance()->GetOnMap())
		{
			// マップ内をクリックした
			if (Battlefield::GetBattlefieldInstance()->GetClickedTileIndex() == gridIndex)
			{
				if (isSelected)
				{
					// 立っているタイルがクリックされた かつ ユニット選択中
					// 選択状態を解除
					isSelected = false;
				}
				else
				{
					// 立っているタイルがクリックされた かつ ユニット未選択
					//ユニットの選択状況をtrueに
					isSelected = true;
					ResetQue();
				}
				
			}
			else if (distanceGrid[Battlefield::GetBattlefieldInstance()->GetClickedTileIndex()] <= movePower && isSelected)
			{
				// 移動範囲内のタイルがクリックされた かつ ユニット選択中
				// 移動処理の開始
				isMoving = true;
				MakePath(Battlefield::GetBattlefieldInstance()->GetClickedTileIndex());
				moveIntervalCount = 0.25;
			}
		}
		else
		{
			// マップ外をクリック
			// 選択状態を解除
			isSelected = false;
		}
	}

	// 各マスへの距離を算出
	CalcurateDistanceGrid();

	// 移動処理
	UnitMove();

	// 描画位置の計算
	drawPosition = Battlefield::GetBattlefieldInstance()->ToTileBottomCenter(gridIndex, 12);
}

void UnitBase::Draw()
{
	// 移動可能地形を表示
	if (isSelected)
	{
		Battlefield::GetBattlefieldInstance()->DrawMoveRange(distanceGrid, movePower);
	}

	// ユニットの描画
	unitTexture
		.mirrored(flipX).scaled(unitScale)
		.draw(
			Arg::bottomCenter = drawPosition
			.moveBy(0, -Battlefield::GetBattlefieldInstance()->TILE_THICKNESS - Battlefield::GetBattlefieldInstance()->TILE_OFFSET.y / 2));
}

void UnitBase::SetUnitParameter()
{
	unitTexture = TextureAsset(PLAYER_BASE);
	gridIndex = { 11, 11 };
	movePower = 4;
}

void UnitBase::UnitMove()
{
	// DeltaTimeに応じてカウントアップ
	moveIntervalCount += Scene::DeltaTime();

	// 閾値を超えたら一マス進む
	if (moveIntervalCount > 0.1)
	{
		if (routePath.empty())
		{
			// 配列が空、つまり目的地に着いた
			isMoving = false;
		}
		else
		{
			// 経路配列の先頭を辿りながら消去
			if (routePath.front().x < gridIndex.x ||
				routePath.front().y > gridIndex.y)
			{
				flipX = true;
			}
			if (routePath.front().x > gridIndex.x ||
				routePath.front().y < gridIndex.y)
			{
				flipX = false;
			}

			gridIndex = routePath.front();
			routePath.pop_front();
		}

		// カウントリセット
		moveIntervalCount = 0;
	}
}

void UnitBase::MakePath(Point targetPoint)
{
	// 選択状態を解除
	isSelected = false;

	// 経路用配列をリセット
	routePath.clear();

	// 目的地を設定
	routePath.push_back(targetPoint);

	while (routePath.front() != gridIndex)
	{
		// 範囲for文で、隣接4マスの始点からの距離を評価
		for (const auto& offset : OFFSETS)
		{
			// 次の探索目標を設定
			const Point nextPosition = (routePath.front() + offset);

			// 範囲外アクセスを防ぐcontinue
			if (!(nextPosition.x < distanceGrid.width() && nextPosition.y < distanceGrid.height()))
			{
				continue;
			}

			// 隣接するマスの中で、侵入可能かつ最も始点に近いものを格納
			if (Battlefield::GetBattlefieldInstance()->GetCanEnterGrid()[nextPosition] &&
				distanceGrid[nextPosition] < distanceGrid[routePath.front()])
			{
				routePath.push_front(nextPosition);
			}
		}
	}
}

void UnitBase::ResetQue()
{
	// 経路をリセットし、現在位置を再設定
	q.clear();
	q.push_back(gridIndex);

	// 距離の二次元配列を再計算
	distanceGrid.fill(INF);
	distanceGrid[gridIndex] = 0;
}

void UnitBase::CalcurateDistanceGrid()
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
}
