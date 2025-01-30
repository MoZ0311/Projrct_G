#include "TitleScene.hpp"
#include "NovelScene.hpp"
#include "GameScene.hpp"
#include "GameOverScene.hpp"

#include "Constants.hpp"

void Main()
{
	// フォントのアセット化
	FontAsset::Register(U"MAKINAS", FontMethod::MSDF, 48, U"font/Makinas-4-Square.otf");

	// テクスチャのアセット化
	TextureAsset::Register(U"PlayerBase", U"image/player/player.png", TextureDesc::Mipped);
	TextureAsset::Register(U"PlayerIdol", U"image/player/player_idol.png", TextureDesc::Mipped);
	TextureAsset::Register(U"PlayerWalk_01", U"image/player/player_walk01.png", TextureDesc::Mipped);
	TextureAsset::Register(U"PlayerWalk_02", U"image/player/player_walk02.png", TextureDesc::Mipped);

	// ウィンドウの名前設定
	Window::SetTitle(U"世界復興計画");

	// ウィンドウサイズの変更
	Window::Resize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// 各シーンの登録
	App manager;
	manager.add<TitleScene>(State::TITLE);
	manager.add<NovelScene>(State::NOVEL);
	manager.add<GameScene>(State::GAME);
	manager.add<GameOverScene>(State::OVER);

	// 最初のシーンを初期化
	manager.init(State::TITLE, 0.5s);

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
