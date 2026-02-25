// NovelScene class

#include "NovelScene.hpp"

NovelScene::NovelScene(const InitData& init)
	:IScene{ init }
{
	Scene::SetBackground(ColorF{ 0.502, 0, 0 });

	// CSVファイルの読み込み
	csv.load(TEXT_DATA_FILE);
	if (!csv)
	{
		throw Error{ U"CSVファイルが読み込めません" };
	}

	textIndex = 1;

	iconTexture = TextureAsset(RANGER_RED_BASE);
	messageText = csv[textIndex][TEXT_COLUMN];
	displayTextLength = 0;
	typeInterval = 0.1;
	finishSentence = false;
}

NovelScene::~NovelScene()
{

}

void NovelScene::update()
{
	// 設定した秒数で文字送り
	displayTextLength += 1 / typeInterval * Scene::DeltaTime();

	// テキストの表示が済んでいるか
	if (displayTextLength > messageText.length())
	{
		finishSentence = true;
	}
	else
	{
		finishSentence = false;
	}

	// アイコンの設定
	switch (Parse<int32>(csv[textIndex][CHARACTER_COLUMN]))
	{
	case ICON_PLAYER:
		iconTexture = TextureAsset(PLAYER_BASE);
		break;

	case ICON_RED:
		iconTexture = TextureAsset(RANGER_RED_BASE);
		break;

	default:
		break;
	}

	// 左クリックでテキスト送り
	if (MouseL.down())
	{
		if (finishSentence)
		{
			if (textIndex < csv.rows() - 1)
			{
				messageText = csv[++textIndex][TEXT_COLUMN];
				displayTextLength = 0;
			}
			else
			{
				// シーンチェンジ演出など
				changeScene(State::BATTLE, 1s);
			}
		}
		else
		{
			displayTextLength = static_cast<double>(messageText.length());
		}
	}
}

void NovelScene::draw() const
{
	// メッセージウィンドウの描画
	MESSAGE_WINDOW.draw(ColorF{ 0, 0.8 }).drawFrame(FRAME_THICKNESS, 0, ColorF{ 0.8 });
	FontAsset(FONT_MAKINAS)(messageText.substr(0, static_cast<size_t>(displayTextLength))).draw(FONT_SIZE, ICON_WINDOW.w + FRAME_THICKNESS * 2 + FONT_SIZE / 2, ICON_WINDOW.y + FONT_SIZE / 5);

	// アイコンの描画
	ICON_WINDOW.draw(ColorF{ 0.5 }).drawFrame(0, FRAME_THICKNESS, ColorF{ 0.8 });
	ICON_WINDOW(iconTexture(16, 0, 96, 96)).draw();
}

void NovelScene::drawFadeOut(double t) const
{
	draw();
	const double r = Scene::Center().length();
	Circle(Scene::Center(), r).drawPie(0_deg, t * 360_deg, Palette::Black);
}
