// Player class

#include "Player.hpp"

#include "Stage.hpp"

// インスタンスをnullptrで初期化
Player* Player::playerInstance = nullptr;

Player::Player(GameScene* instance)
{
	gameSceneInstance = instance;
	playerPosition = { 0, 185 };
	prevPlayerPosition = { 0, 185 };
	playerMovement = { 0, 0 };
	flipX = false;
	isIdol = true;
	animationSpeed = 0;
	animationCount = 0;
	onMap = true;
}

Player::~Player()
{

}

void Player::Init(GameScene* instance)
{
	if (playerInstance != nullptr)
	{
		return;
	}

	playerInstance = new Player(instance);
}

void Player::Release()
{
	if (playerInstance != nullptr)
	{
		delete playerInstance;
		playerInstance = nullptr;
	}
}

void Player::Update()
{
	Move();
}

void Player::Move()
{
	// キー入力を二次元ベクトルに
	int32 upInput = KeyW.pressed() ? 1 : 0;
	int32 downInput = KeyS.pressed() ? 1 : 0;
	int32 leftInput = KeyA.pressed() ? 1 : 0;
	int32 rightInput = KeyD.pressed() ? 1: 0;

	playerMovement = { rightInput - leftInput, downInput - upInput };

	// アイドル状態の判定
	isIdol = playerMovement.isZero();

	// 左右反転の判定
	if (playerMovement.x < 0)
	{
		flipX = true;
	}
	if (playerMovement.x > 0)
	{
		flipX = false;
	}

	// 移動処理
	playerPosition.moveBy(playerMovement.setLength(MOVE_SPEED)* Scene::DeltaTime());

	// マップの判定を取得
	Polygon mapCollider = Stage::GetStageInstance()->GetMapCollider();

	// プレイヤーの判定を生成
	playerCollider = Shape2D::Rhombus(
		TextureAsset(U"PlayerBase").width() * PLAYER_SCALE / 1.5,
		TextureAsset(U"PlayerBase").width() * PLAYER_SCALE / 3,
		playerPosition.movedBy(0, TextureAsset(U"PlayerBase").height() * PLAYER_SCALE / 2));

	// マップ上かの真偽判定
	onMap = mapCollider.contains(playerCollider);

	if (onMap)
	{
		// 直前表示座標を更新
		prevPlayerPosition = playerPosition;
	}
	else
	{
		// 直前座標に戻す
		playerPosition = prevPlayerPosition;
	}
}

void Player::Draw()
{
	// 描画に使用するテクスチャ配列
	Array<Texture> animation;
	if (isIdol || gameSceneInstance->GetIsEditing())
	{
		// 移動ベクトルが0、または編集中はアイドルモーションが適用
		animationSpeed = IDOL_ANIMATION_SPEED;
		animation = PLAYER_IDOL_ARRAY;
	}
	else
	{
		animationSpeed = WALK_ANIMATION_SPEED;
		animation = PLAYER_WALK_ARRAY;
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

	// プレイヤーを描く
	if (gameSceneInstance->GetIsEditing())
	{
		// 編集中であれば、透明にする
		animation[index].
			mirrored(flipX).
			scaled(PLAYER_SCALE).
			drawAt(playerPosition.x, playerPosition.y,
				ColorF{1, 0.3}
			);
	}
	else
	{
		animation[index].
			mirrored(flipX).
			scaled(PLAYER_SCALE).
			drawAt(playerPosition.x, playerPosition.y
			);
	}
}

Player* Player::GetPlayerInstance()
{
	return playerInstance;
}

Vec2 Player::GetPlayerPosition() const
{
	return playerPosition;
}
