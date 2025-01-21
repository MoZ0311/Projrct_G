#include "TitleScene.hpp"
#include "GameScene.hpp"
#include "GameOverScene.hpp"

#include "Constants.hpp"

void Main()
{
	// フォントのアセット化
	FontAsset::Register(U"MAKINAS", FontMethod::MSDF, 48, U"font/Makinas-4-Square.otf");

	// ウィンドウの名前設定
	Window::SetTitle(U"世界復興計画");

	// ウィンドウサイズの変更
	Window::Resize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// 各シーンの登録
	App manager;
	manager.add<TitleScene>(State::TITLE);
	manager.add<GameScene>(State::GAME);
	manager.add<GameOverScene>(State::OVER);

	manager.init(State::GAME, 0.5s);

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
