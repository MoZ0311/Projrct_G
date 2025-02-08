// Player class

#pragma once

#include "GameScene.hpp"
#include "Constants.hpp"

class Player
{
public:

	// 初期化処理
	static void Init(GameScene* instance);

	// 解放処理
	static void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

	// インスタンスのゲッター関数
	static Player* GetPlayerInstance();

	// プレイヤー座標のゲッター関数
	Vec2 GetPlayerPosition() const;

	// プレイヤーの移動ベクトルのゲッター関数
	Vec2 GetPlayerMovement() const;

private:

	// コンストラクタ
	Player(GameScene* instance);

	// デストラクタ
	~Player();

	// 移動処理
	void Move();

	// シングルトンクラスのインスタンスのポインタ
	static Player* playerInstance;

	// GameScene クラスのインスタンスのポインタ
	GameScene* gameSceneInstance;

	// テクスチャを配列として確保
	const Array<Texture> PLAYER_IDOL_ARRAY = {
		TextureAsset(PLAYER_BASE), TextureAsset(PLAYER_IDOL)
	};

	const Array<Texture> PLAYER_WALK_ARRAY = {
		TextureAsset(PLAYER_BASE), TextureAsset(PLAYER_WALK_01),
		TextureAsset(PLAYER_WALK_02), TextureAsset(PLAYER_WALK_01)
	};

	// プレイヤーの描画スケール
	const double PLAYER_SCALE = 0.5;

	// プレイヤーの移動スピード
	const double MOVE_SPEED = 150;

	// アイドルアニメーションの再生速度
	const double IDOL_ANIMATION_SPEED = 3;

	// 歩行アニメーションの再生速度
	const double WALK_ANIMATION_SPEED = 10;

	// プレイヤーの当たり判定用図形
	Polygon playerCollider;

	// プレイヤーの表示座標
	Vec2 playerPosition;

	// プレイヤーの直前表示座標
	Vec2 prevPlayerPosition;

	// プレイヤーの移動ベクトル
	Vec2 playerMovement;

	// 左右反転するか
	bool flipX;

	// アイドル状態か
	bool isIdol;

	// アニメーション再生速度
	double animationSpeed;

	// アニメーションカウント
	double animationCount;

	// マップ上に立っているか
	bool onMap;
};
