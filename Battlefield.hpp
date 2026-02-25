// Battlefield class

#pragma once

#include "MapBase.hpp"
#include "UnitBase.hpp"

class Battlefield : public MapBase
{
public:

	// 初期化処理
	static void Init();

	// 解放処理
	static void Release();

	// 更新処理
	void Update() override;

	// 移動範囲の描画
	void DrawMoveRange(Grid<int32> distanceGrid, int32 movePower);

	// マップの侵入可能、不可能の導出
	Grid<bool> GetCanEnterGrid(Point gridPosition) const;

	// インスタンスのゲッター関数
	static Battlefield* GetBattlefieldInstance();

	// マップの二次元配列のゲッター関数
	Grid<int32> GetGrid() const;

	// クリックされたタイルのゲッター関数
	Point GetClickedTileIndex() const;

	// マウスがマップ上にあるかのゲッター関数
	bool GetOnMap() const;

private:

	// 読み込み対象のCSVを設定する
	void SetMapDataFilePath() override;

	// マップデータのセーブ処理
	void SaveMapData() override;

	// グリッドの描画
	void DrawGrid() override;

	// シングルトンクラスのインスタンスのポインタ
	static Battlefield* battlefieldInstance;

	// マップの強調表示の青色
	static constexpr ColorF CLEAR_BLUE{ 0.0, 0.0, 1.0, 0.3 };

	// マップの強調表示の赤色
	static constexpr ColorF CLEAR_RED{ 1.0, 0.0, 0.0, 0.3 };

	// グリッドの引き延ばし
	static constexpr double GRID_STRETCH = 1.2;

	// クリックされたタイルのインデックス
	Point clickedTileIndex;
};
