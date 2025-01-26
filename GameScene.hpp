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

	// ゲームモードを変更できるかの判定処理
	bool CanGameModeChange() const;

	// テクスチャ配列のゲッター関数
	Array<Texture> GetTileTextureArray();

	// エディット中かのゲッター関数
	bool GetIsEditing();

private:

	/// @brief 画像を読み込み、アルファ乗算済みのテクスチャを作成します。
	/// @param path 画像ファイルのパス
	/// @return アルファ乗算済みのテクスチャ
	/// @remark 境界付近の品質を向上させるため、アルファ乗算済みのテクスチャを作成します。
	/// @remark 描画時は `BlendState::Premultiplied` を指定してください。
	Texture LoadPremultipliedTexture(FilePathView path);

	// タイルのテクスチャ配列
	Array<Texture> tileTextureArray;

	// マップ表示用の 2D カメラ
	Camera2D camera;

	// マップのエディット中か
	bool isEditing;
};
