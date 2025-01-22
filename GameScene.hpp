// GameScene class

#pragma once

#include "Common.hpp"

class GameScene : public App::Scene
{
public:

	// コンストラクタ
	GameScene(const InitData& init);

	// デストラクタ
	~GameScene();

	// 更新処理
	void update() override;

	// 描画処理
	void draw() const override;

	// テクスチャ配列のゲッター関数
	Array<Texture> GetTileTextureArray();

	// エディット中かのゲッター関数
	bool GetIsEditing();

private:

	// タイルのテクスチャ配列
	Array<Texture> tileTextureArray;

	// マップ表示用の 2D カメラ
	Camera2D camera;

	// マップのエディット中か
	bool isEditing;
};
