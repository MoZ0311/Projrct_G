// GameScene class

#include "GameScene.hpp"

#include "Player.hpp"
#include "TownField.hpp"
#include "UI.hpp"

GameScene::GameScene(const InitData& init)
	:IScene{ init }
{
	// TownField class の生成
	TownField::Init(this);

	// Player class の生成
	Player::Init(this);

	// UI class の生成
	UI::Init();

	// 背景の色を設定する
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	// ストップウォッチ設定
	stopwatch.start();

	// カメラの倍率を設定
	camera.setTargetScale(1.5);

	// ゲームモード設定
	isEditing = false;

	mapNamePosition = { 20, 20 };
	mapStatusPosition = { SCREEN_WIDTH - 320, 20 };
	prevVector = {};
	currentVector = {};
}

GameScene::~GameScene()
{
	// TownField class の解放
	TownField::Release();

	// Player class の解放
	Player::Release();

	// UI class の解放
	UI::Release();
}

void GameScene::update()
{
	// 2D カメラを更新する
	camera.update();

	{
		const auto tr = camera.createTransformer();

		if (isEditing)
		{
			// TownField class の更新処理
			TownField::GetTownFieldInstance()->Update();
		}
		else
		{
			// Player class の更新処理
			Player::GetPlayerInstance()->Update();
		}
	}

	if (isEditing)
	{
		// カメラを操作可能に
		camera.setParameters(Camera2DParameters::MouseOnly());

		// UI class の更新処理
		UI::GetUIInstance()->Update();
	}
	else
	{
		// カメラを操作不能に
		camera.setParameters(Camera2DParameters::NoControl());

		// カメラをプレイヤーに追従
		camera.setTargetCenter(Player::GetPlayerInstance()->GetPlayerPosition());
		camera.setTargetScale(1.5);

		// マップ名の表示位置の変更
		prevVector = currentVector;
		currentVector = Player::GetPlayerInstance()->GetPlayerMovement();

		if (currentVector.isZero())
		{
			if (!prevVector.isZero())
			{
				stopwatch.restart();
			}
			mapNamePosition.x = 20;
			mapStatusPosition.x = SCREEN_WIDTH - 320;
		}
		else
		{
			mapNamePosition.x -= Scene::DeltaTime() * 800;
			mapStatusPosition.x += Scene::DeltaTime() * 800;
			if (mapNamePosition.x < -500)
			{
				mapNamePosition.x = -500;
			}
			if (mapStatusPosition.x > SCREEN_WIDTH)
			{
				mapStatusPosition.x = SCREEN_WIDTH;
			}
		}
	}

	// ゲームモードの切り替え
	if (KeyF.down())
	{

		ClearPrint();
		if (CanGameModeChange())
		{
			if (!isEditing)
			{
				// エディットモードになる時、カメラを再設定
				camera.setTargetCenter(Vec2{ 0, 105 });
				camera.setTargetScale(0.85);
			}
			else
			{
				// プレイモードになるとき、ストップウォッチをリセット
				stopwatch.restart();
			}
			
			isEditing = !isEditing;
		}
		else
		{
			Print << U"セーブしろ!!!";
		}
	}

	// カメラリセット
	if (MouseM.down() && isEditing)
	{
		camera.setTargetCenter(Vec2{ 0, 105 });
		camera.setTargetScale(0.85);
	}
}

void GameScene::draw() const
{
	{
		const auto tr = camera.createTransformer();

		// TownField class の描画処理
		TownField::GetTownFieldInstance()->Draw();

		// Player class の描画処理
		Player::GetPlayerInstance()->Draw();
	}

	if (isEditing)
	{
		// UI class の描画処理
		UI::GetUIInstance()->Draw();

		// 2D カメラの UI を表示する
		camera.draw(Palette::Deepskyblue);
	}
	else
	{
		const double t = stopwatch.sF();
		const Array<int32> MAP_STATUS = TownField::GetTownFieldInstance()->GetMapStatus();

		DrawText(
			FontAsset(FONT_MAKINAS), 32,
			U"街区\n",
			mapNamePosition, ColorF{ 0, 0, 1 }, t, 0.08
		);

		DrawText(
			FontAsset(FONT_MAKINAS), 32,
			U"水源:{: >4} 都会:{: >4}\n自然:{: >4} 荒廃:{: >4}\n"_fmt(MAP_STATUS[0], MAP_STATUS[1], MAP_STATUS[2], MAP_STATUS[3]),
			mapStatusPosition, ColorF{0, 0, 1}, t, 0.02
		);
	}
}

bool GameScene::CanGameModeChange() const
{
	if (isEditing)
	{
		return TownField::GetTownFieldInstance()->MapEqualsCSV();
	}

	return true;
}

void GameScene::DrawText(const Font& font, double fontSize, const String& text, const Vec2& pos, const ColorF& color, double t, double characterPerSec) const
{
	const double scale = (fontSize / font.fontSize());
	Vec2 penPos = pos;
	const ScopedCustomShader2D shader{ Font::GetPixelShader(font.method()) };
	ClearPrint();
	for (auto&& [i, glyph] : Indexed(font.getGlyphs(text)))
	{
		if (glyph.codePoint == U'\n')
		{
			penPos.x = pos.x;
			penPos.y += (font.height() * scale);
			continue;
		}

		const double targetTime = (i * characterPerSec);

		if (t < targetTime)
		{
			break;
		}

		const double y = EaseInQuad(Saturate(1 - (t - targetTime) / 0.3)) * -20.0;
		const double a = Min((t - targetTime) / 0.3, 1.0);
		glyph.texture.scaled(scale).draw(penPos + glyph.getOffset(scale) + Vec2{ 0, y }, ColorF{ color, a });

		penPos.x += (glyph.xAdvance * scale);
	}
}

bool GameScene::GetIsEditing() const
{
	return isEditing;
}
