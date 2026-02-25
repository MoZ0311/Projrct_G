// GameScene class

#include "GameScene.hpp"

#include "Player.hpp"
#include "Townfield.hpp"
#include "UI.hpp"

GameScene::GameScene(const InitData& init)
	:IScene{ init }
{
	// Townfield class の生成
	Townfield::Init(this);
	Townfield::GetTownFieldInstance()->LoadMapData();

	// Player class の生成
	Player::Init(this);

	// UI class の生成
	UI::Init();

	// ストップウォッチ設定
	stopwatch.start();

	// カメラの倍率を設定
	camera.setTargetScale(1.5);

	// ゲームモード設定
	isEditing = false;

	// メンバ変数の初期化
	mapStatusArray = { 0, 0, 0, 0 };
	mapNamePosition = { 20, 20 };
	mapStatusPosition = { SCREEN_WIDTH - 320, 20 };
	idolCount = 0.5;
	mapTitle = U"";
}

GameScene::~GameScene()
{
	// Townfield class の解放
	Townfield::Release();

	// Player class の解放
	Player::Release();

	// UI class の解放
	UI::Release();
}

void GameScene::update()
{
	// マップのステータスを取得
	SetMapTitle();

	// 2D カメラを更新する
	camera.update();

	{
		// カメラ移動を適用
		const auto tr = camera.createTransformer();

		if (isEditing)
		{
			// Townfield class の更新処理
			Townfield::GetTownFieldInstance()->Update();
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

		// プレイヤーの移動入力を取得
		Vec2 inputVector = Player::GetPlayerInstance()->GetPlayerMovement();

		if (inputVector.isZero())
		{
			idolCount += Scene::DeltaTime();

			if (idolCount <= 0.5)
			{
				// 一定時間停止状態でUI表示
				stopwatch.reset();
				mapNamePosition.x = 20;
				mapStatusPosition.x = SCREEN_WIDTH - 320;
			}
			else
			{
				stopwatch.start();
			}
		}
		else
		{
			// 停止カウントをリセット
			idolCount = 0;

			// 移動中なら画面外に向けてUIを移動
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
			Print << U"セーブされていません";
		}
	}

	// カメラリセット
	if (MouseM.down() && isEditing)
	{
		camera.setTargetCenter(Vec2{ 0, 105 });
		camera.setTargetScale(0.85);
	}

	// シーン切替
	if (KeyQ.down())
	{
		changeScene(State::TITLE, 0.5s);
	}
}

void GameScene::draw() const
{
	// グラデーション背景の描画
	DrawVerticalGradientBackground(ColorF{ 0.529, 0.808, 0.922 }, ColorF{ 0.545, 0.271, 0.075 });

	{
		const auto tr = camera.createTransformer();

		// Townfield class の描画処理
		Townfield::GetTownFieldInstance()->Draw();

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
		// ストップウォッチの経過を取得
		const double t = stopwatch.sF();

		// マップ名を描画
		DrawText(
			FontAsset(FONT_MAKINAS), 32,
			mapTitle,mapNamePosition,
			ColorF{ 1.0, 0.98, 0.941 }, t, 0.08
		);

		// 詳細ステータスを描画
		DrawText(
			FontAsset(FONT_MAKINAS), 32,
			U"水源:{:0>3} 都会:{:0>3}\n自然:{:0>3} 荒廃:{:0>3}\n"_fmt(mapStatusArray[0], mapStatusArray[1], mapStatusArray[2], mapStatusArray[3]),
			mapStatusPosition, ColorF{ 1.0, 0.98, 0.941 }, t, 0.02
		);
	}
}

bool GameScene::CanGameModeChange() const
{
	if (isEditing)
	{
		return Townfield::GetTownFieldInstance()->MapEqualsCSV();
	}

	return true;
}

void GameScene::SetMapTitle()
{
	for (int32 i = 0; i < mapStatusArray.size(); ++i)
	{
		mapStatusArray[i] = Townfield::GetTownFieldInstance()->GetMapStatus()[i];
	}

	String front = U"";
	String back = U"";

	if (mapStatusArray[ROUGH] == 338)
	{
		mapTitle = U"一面の焼野原";
	}
	else if (mapStatusArray[MOISTURE] == 169)
	{
		mapTitle = U"ただの湖";
	}
	else if (mapStatusArray[NATURE] == 19 &&
			 mapStatusArray[URBAN] == 156)
	{
		mapTitle = U"サイクロンメタル";
	}
	else 
	{
		if (mapStatusArray[NATURE] >= 100)
		{
			back = U"草原";
		}
		else if (mapStatusArray[NATURE] >= 40)
		{
			front = U"緑のある";
		}

		if (mapStatusArray[MOISTURE] >= 100)
		{
			back = U"孤島";
		}
		else if (mapStatusArray[MOISTURE] >= 52)
		{
			front = U"水の";
		}
		else if (mapStatusArray[MOISTURE] >= 13)
		{
			front = U"潤う";
		}		

		if (mapStatusArray[URBAN] >= 70)
		{
			back = U"街";
		}

		if (mapStatusArray[ROUGH] >= 100)
		{
			back = U"荒地";
		}
		else if (mapStatusArray[ROUGH] >= 20)
		{
			front = U"不気味な";
		}

		if (front == U"")
		{
			front = U"謎の";
		}
		if (back == U"")
		{
			back = U"場所";
		}

		mapTitle = front + back;
	}
	
	
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

		const Vec2 offSet{ 1.5, 1.5 };
		const double y = EaseInQuad(Saturate(1 - (t - targetTime) / 0.3)) * -20.0;
		const double a = Min((t - targetTime) / 0.3, 1.0);
		glyph.texture.scaled(scale).draw(penPos + glyph.getOffset(scale) + offSet + Vec2{ 0, y }, ColorF{ 0, a });
		glyph.texture.scaled(scale).draw(penPos + glyph.getOffset(scale) + Vec2{ 0, y }, ColorF{ color, a });

		penPos.x += (glyph.xAdvance * scale);
	}
}

bool GameScene::GetIsEditing() const
{
	return isEditing;
}
