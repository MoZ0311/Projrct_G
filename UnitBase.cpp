// UnitBase class

#include "UnitBase.hpp"
#include "Battlefield.hpp"
#include "UnitManager.hpp"

UnitBase::UnitBase()
{
	drawPosition = {};
	distanceGrid = { Battlefield::GetBattlefieldInstance()->GetGrid().size(), INF };
	routePath = {};
	UnitActionRefresh();
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
	// 移動中でない, 移動後でない, 行動後でない, 状態でのみ反応する
	if (!isMoving && !hasMoved && !finishAction && MouseL.down())
	{
		// 前提として、移動中のクリックは受付けない
		if (Battlefield::GetBattlefieldInstance()->GetOnMap())
		{
			// マップ内をクリックした
			if (Battlefield::GetBattlefieldInstance()->GetClickedTileIndex() == gridPosition)
			{
				if (isSelected)
				{
					// 立っているタイルがクリックされた かつ ユニット選択中
					// 選択状態を解除
					isSelected = false;
					hasMoved = true;
				}
				else if (!UnitManager::GetUnitManagerInstance()->GetUnitControll())
				{
					// 立っているタイルがクリックされた かつ ユニット未選択
					//ユニットの選択状況をtrueに
					UnitManager::GetUnitManagerInstance()->SetUnitControll(true);
					isSelected = true;
					ResetQue();
				}
				
			}
			else if (distanceGrid[Battlefield::GetBattlefieldInstance()->GetClickedTileIndex()] <= movePower && isSelected)
			{
				// 移動範囲内のタイルがクリックされた かつ ユニット選択中
				// 移動処理の開始
				MakePath(Battlefield::GetBattlefieldInstance()->GetClickedTileIndex());
				moveIntervalCount = 0.25;
			}
		}
		else
		{
			// マップ外をクリック
			// 選択状態を解除
			UnitManager::GetUnitManagerInstance()->SetUnitControll(false);
			isSelected = false;
		}
	}

	// 各マスへの距離を算出
	CalcurateDistanceGrid();

	// 移動処理
	UnitMove();
}

void UnitBase::Draw()
{
	// 描画に使用するテクスチャ配列
	Array<Texture> animation;
	if (isMoving)
	{
		// 移動中なので、歩行モーションを適用
		animationSpeed = WALK_ANIMATION_SPEED;
		animation = unitWalkArray;
	}
	else
	{
		// アイドルモーションが適用
		animationSpeed = IDOL_ANIMATION_SPEED;
		animation = unitIdolArray;
	}

	// アニメーションを進める
	animationCount += Scene::DeltaTime() * animationSpeed;
	int32 index = static_cast<int32>(animationCount);

	// アニメーションのリセット
	if (index >= animation.size())
	{
		index = 0;
		animationCount = 0;
	}

	// 描画位置の計算
	drawPosition = Battlefield::GetBattlefieldInstance()->ToTileBottomCenter(gridPosition, MapBase::TILE_NUM);

	// ユニットの描画
	if (hasMoved)
	{
		// 移動後は暗く描画
		animation[index]
			.mirrored(flipX).scaled(unitScale)
			.draw(Arg::bottomCenter = drawPosition.moveBy(
				0, -MapBase::TILE_THICKNESS - MapBase::TILE_OFFSET.y / 2),
				ColorF{ 0.5 });
	}
	else
	{
		animation[index]
			.mirrored(flipX).scaled(unitScale)
			.draw(Arg::bottomCenter = drawPosition.moveBy(
				0, -MapBase::TILE_THICKNESS - MapBase::TILE_OFFSET.y / 2));
	}
	
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
			if (isMoving)
			{
				hasMoved = true;
				UnitManager::GetUnitManagerInstance()->SetUnitControll(false);
			}

			isMoving = false;
		}
		else
		{
			// 経路配列の先頭を辿りながら消去
			if (routePath.front().x < gridPosition.x ||
				routePath.front().y > gridPosition.y)
			{
				flipX = true;
			}
			if (routePath.front().x > gridPosition.x ||
				routePath.front().y < gridPosition.y)
			{
				flipX = false;
			}

			gridPosition = routePath.front();
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

	// 移動中である
	isMoving = true;

	// 経路用配列をリセット
	routePath.clear();

	// 目的地を設定
	routePath.push_back(targetPoint);

	while (routePath.front() != gridPosition)
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
			if (Battlefield::GetBattlefieldInstance()->GetCanEnterGrid(gridPosition)[nextPosition] &&
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
	q.push_back(gridPosition);

	// 距離の二次元配列を再計算
	distanceGrid.fill(INF);
	distanceGrid[gridPosition] = 0;
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
			if (Battlefield::GetBattlefieldInstance()->GetCanEnterGrid(gridPosition)[nextPosition] &&
				currentDistance + 1 < distanceGrid[nextPosition])
			{
				distanceGrid[nextPosition] = (currentDistance + 1);
				q.push_back(nextPosition);
			}
		}
	}
}

void UnitBase::UnitActionRefresh()
{
	isSelected = false;
	isMoving = false;
	hasMoved = false;
	finishAction = false;
}

Grid<int32> UnitBase::GetDistanceGrid() const
{
	return distanceGrid;
}

Point UnitBase::GetGridPosition() const
{
	return gridPosition;
}

int32 UnitBase::GetMovePower() const
{
	return movePower;
}

bool UnitBase::GetIsSelected() const
{
	return isSelected;
}

bool UnitBase::GetHasMoved() const
{
	return hasMoved;
}

bool UnitBase::GetFinishAction() const
{
	return finishAction;
}

void UnitBase::SetFinishAction(bool value)
{
	finishAction = value;
}
