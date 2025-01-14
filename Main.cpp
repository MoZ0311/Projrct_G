# include <Siv3D.hpp>

#include "Player.hpp"

void Main()
{
	Player::Init();
	while (System::Update())
	{
		Player::GetPlayerInstance()->Update();
		Player::GetPlayerInstance()->Draw();
	}
	Player::Release();
}
