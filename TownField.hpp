// Townfield class

#pragma once

#include "MapBase.hpp"
#include "GameScene.hpp"

class Townfield : public MapBase
{
public:

	// 初期化処理
	static void Init(GameScene* instance);

	// 解放処理
	static void Release();

	// インスタンスのゲッター関数
	static Townfield* GetTownFieldInstance();

	// マップのステータス算出処理
	Array<int32> GetMapStatus() const;

	// マップ端の当たり判定用図形
	const Polygon MAP_COLLIDER = Shape2D::Rhombus(
		TILE_OFFSET.x * 2 * tileNum,
		TILE_OFFSET.y * 2 * tileNum,
		Vec2{ 0, TILE_OFFSET.y * tileNum - TILE_THICKNESS - TILE_OFFSET.y * 2 }
	);

private:

	// コンストラクタ
	Townfield(GameScene* instance);

	// 読み込み対象のCSVを設定する
	void SetMapDataFilePath() override;

	// タイルの強調表示
	void DrawTileHighlight() override;

	// グリッドの描画
	void DrawGrid() override;

	// シングルトンクラスのインスタンスのポインタ
	static Townfield* townFieldInstance;

	// GameScene class のインスタンスのポインタ
	GameScene* gameSceneInstance;
};
