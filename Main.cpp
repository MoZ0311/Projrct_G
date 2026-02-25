#include "TitleScene.hpp"
#include "NovelScene.hpp"
#include "BattleScene.hpp"
#include "GameScene.hpp"
#include "GameOverScene.hpp"

#include "Constants.hpp"

void Main()
{
	// フォントのアセット化
	FontAsset::Register(FONT_MAKINAS, FontMethod::MSDF, 48, U"font/Makinas-4-Square.otf");
	const Font EMOJI{ FontMethod::MSDF, 48, Typeface::ColorEmoji };

	FontAsset(FONT_MAKINAS).addFallback(EMOJI);

	// テクスチャのアセット化
	TextureAsset::Register(PLAYER_BASE, U"image/player/player.png", TextureDesc::Mipped);
	TextureAsset::Register(PLAYER_IDOL, U"image/player/player_idol.png", TextureDesc::Mipped);
	TextureAsset::Register(PLAYER_WALK_01, U"image/player/player_walk01.png", TextureDesc::Mipped);
	TextureAsset::Register(PLAYER_WALK_02, U"image/player/player_walk02.png", TextureDesc::Mipped);

	TextureAsset::Register(RANGER_ALPHA_BASE, U"image/ranger/alpha1.png", TextureDesc::Mipped);
	TextureAsset::Register(RANGER_ALPHA_IDOL, U"image/ranger/alpha2.png", TextureDesc::Mipped);
	TextureAsset::Register(RANGER_ALPHA_WALK_01, U"image/ranger/alpha3.png", TextureDesc::Mipped);
	TextureAsset::Register(RANGER_ALPHA_WALK_02, U"image/ranger/alpha4.png", TextureDesc::Mipped);

	TextureAsset::Register(RANGER_BLACK_BASE, U"image/ranger/black1.png", TextureDesc::Mipped);
	TextureAsset::Register(RANGER_BLACK_IDOL, U"image/ranger/black2.png", TextureDesc::Mipped);
	TextureAsset::Register(RANGER_BLACK_WALK_01, U"image/ranger/black3.png", TextureDesc::Mipped);
	TextureAsset::Register(RANGER_BLACK_WALK_02, U"image/ranger/black4.png", TextureDesc::Mipped);

	TextureAsset::Register(RANGER_BLUE_BASE, U"image/ranger/blue1.png", TextureDesc::Mipped);
	TextureAsset::Register(RANGER_BLUE_IDOL, U"image/ranger/blue2.png", TextureDesc::Mipped);
	TextureAsset::Register(RANGER_BLUE_WALK_01, U"image/ranger/blue3.png", TextureDesc::Mipped);
	TextureAsset::Register(RANGER_BLUE_WALK_02, U"image/ranger/blue4.png", TextureDesc::Mipped);

	TextureAsset::Register(RANGER_GREEN_BASE, U"image/ranger/green1.png", TextureDesc::Mipped);
	TextureAsset::Register(RANGER_GREEN_IDOL, U"image/ranger/green2.png", TextureDesc::Mipped);
	TextureAsset::Register(RANGER_GREEN_WALK_01, U"image/ranger/green3.png", TextureDesc::Mipped);
	TextureAsset::Register(RANGER_GREEN_WALK_02, U"image/ranger/green4.png", TextureDesc::Mipped);

	TextureAsset::Register(RANGER_PINK_BASE, U"image/ranger/pink1.png", TextureDesc::Mipped);
	TextureAsset::Register(RANGER_PINK_IDOL, U"image/ranger/pink2.png", TextureDesc::Mipped);
	TextureAsset::Register(RANGER_PINK_WALK_01, U"image/ranger/pink3.png", TextureDesc::Mipped);
	TextureAsset::Register(RANGER_PINK_WALK_02, U"image/ranger/pink4.png", TextureDesc::Mipped);

	TextureAsset::Register(RANGER_RED_BASE, U"image/ranger/red1.png", TextureDesc::Mipped);
	TextureAsset::Register(RANGER_RED_IDOL, U"image/ranger/red2.png", TextureDesc::Mipped);
	TextureAsset::Register(RANGER_RED_WALK_01, U"image/ranger/red3.png", TextureDesc::Mipped);
	TextureAsset::Register(RANGER_RED_WALK_02, U"image/ranger/red4.png", TextureDesc::Mipped);

	// ウィンドウの名前設定
	Window::SetTitle(U"世界復興計画");

	// ウィンドウサイズの変更
	Window::Resize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// 各シーンの登録
	App manager;
	manager.add<TitleScene>(State::TITLE);
	manager.add<NovelScene>(State::NOVEL);
	manager.add<BattleScene>(State::BATTLE);
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
