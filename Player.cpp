// Player class

#include "Player.hpp"

// インスタンスをnullptrで初期化
Player* Player::playerInstance = nullptr;

Player::Player()
{
	playerPosition = Scene::Center();
	playerMovement = { 0, 0 };
	flipX = false;
	isIdol = true;
	animationSpeed = 0;
	animationCount = 0;
}

Player::~Player()
{

}

void Player::Init()
{
	if (playerInstance != nullptr)
	{
		return;
	}

	playerInstance = new Player();
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
	int upInput = static_cast<int>(KeyW.pressed());
	int downInput = static_cast<int>(KeyS.pressed());
	int leftInput = static_cast<int>(KeyA.pressed());
	int rightInput = static_cast<int>(KeyD.pressed());

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

	// 画面外に出ないようにする処理
	playerPosition.x = Clamp(playerPosition.x, static_cast<double>(PLAYER_BASE.width() / 2), static_cast<double>(Scene::Width() - PLAYER_BASE.width() / 2));
	playerPosition.y = Clamp(playerPosition.y, static_cast<double>(PLAYER_BASE.height() / 2), static_cast<double>(Scene::Height() - PLAYER_BASE.height() / 2));
}

void Player::Draw()
{
	// 描画に使用するテクスチャ配列
	Array<Texture> animation;
	if (isIdol)
	{
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
	int index = static_cast<int>(animationCount);

	// アニメーションのリセット
	if (index >= animation.size())
	{
		index = 0;
		animationCount = 0;
	}

	// プレイヤーを描く
	animation[index].mirrored(flipX).drawAt(playerPosition.x, playerPosition.y);
}

Player* Player::GetPlayerInstance()
{
	return playerInstance;
}
