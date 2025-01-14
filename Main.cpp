# include <Siv3D.hpp>

#include "GameScene.hpp"

void Main()
{
	// ウィンドウの名前設定
	Window::SetTitle(U"世界復興計画");

	// ウィンドウサイズの変更
	Window::Resize(1376, 768);

	// 各シーンの登録
	App manager;
	manager.add<GameScene>(State::GAME);

	// メインループ
	while (System::Update())
	{
		if (!manager.update())
		{
			// 更新に失敗で終了
			break;
		}
	}
}
