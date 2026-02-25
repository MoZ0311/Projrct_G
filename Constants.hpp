// 定数定義

#pragma once

constexpr int32 SCREEN_WIDTH = 1366;								// 画面の幅
constexpr int32 SCREEN_HEIGHT = 768;								// 画面の高さ

constexpr int32 INF = 99;											// 無限(非常に大きい数の意)

// アセット用定数
const String FONT_MAKINAS = U"MAKINAS";								// Makinasフォント
const String FONT_EMOJI = U"EMOJI";									// 絵文字

const String PLAYER_BASE = U"PlayerBase";							// プレイヤー基本画像
const String PLAYER_IDOL = U"PlayerIdol";							// プレイヤー待機画像
const String PLAYER_WALK_01 = U"PlayerWalk_01";						// プレイヤー歩行画像01
const String PLAYER_WALK_02 = U"PlayerWalk_02";						// プレイヤー歩行画像02

const String RANGER_ALPHA_BASE = U"RangerAlphaBase";				// アルファ基本画像
const String RANGER_ALPHA_IDOL = U"RangerAlphaIdol";				// アルファ基本画像
const String RANGER_ALPHA_WALK_01 = U"RangerAlphaWalk_01";			// アルファ基本画像
const String RANGER_ALPHA_WALK_02 = U"RangerAlphaWalk_02";			// アルファ基本画像

const String RANGER_BLACK_BASE = U"RangerBlackBase";				// ブラック基本画像
const String RANGER_BLACK_IDOL = U"RangerBlackIdol";				// ブラック基本画像
const String RANGER_BLACK_WALK_01 = U"RangerBlackWalk_01";			// ブラック基本画像
const String RANGER_BLACK_WALK_02 = U"RangerBlackWalk_02";			// ブラック基本画像

const String RANGER_BLUE_BASE = U"RangerBlueBase";					// ブルー基本画像
const String RANGER_BLUE_IDOL = U"RangerBlueIdol";					// ブルー基本画像
const String RANGER_BLUE_WALK_01 = U"RangerBlueWalk_01";			// ブルー基本画像
const String RANGER_BLUE_WALK_02 = U"RangerBlueWalk_02";			// ブルー基本画像

const String RANGER_GREEN_BASE = U"RangerGreenBase";				// グリーン基本画像
const String RANGER_GREEN_IDOL = U"RangerGreenIdol";				// グリーン基本画像
const String RANGER_GREEN_WALK_01 = U"RangerGreenWalk_01";			// グリーン基本画像
const String RANGER_GREEN_WALK_02 = U"RangerGreenWalk_02";			// グリーン基本画像

const String RANGER_PINK_BASE = U"RangerPinkBase";					// ピンク基本画像
const String RANGER_PINK_IDOL = U"RangerPinkIdol";					// ピンク基本画像
const String RANGER_PINK_WALK_01 = U"RangerPinkWalk_01";			// ピンク基本画像
const String RANGER_PINK_WALK_02 = U"RangerPinkWalk_02";			// ピンク基本画像

const String RANGER_RED_BASE = U"RangerRedBase";					// レッド基本画像
const String RANGER_RED_IDOL = U"RangerRedIdol";					// レッド基本画像
const String RANGER_RED_WALK_01 = U"RangerRedWalk_01";				// レッド基本画像
const String RANGER_RED_WALK_02 = U"RangerRedWalk_02";				// レッド基本画像

// 各アニメーションの再生速度
constexpr double IDOL_ANIMATION_SPEED = 3;							// アイドルアニメーションの再生速度
constexpr double WALK_ANIMATION_SPEED = 10;							// 歩行アニメーションの再生速度

// CSVファイルのパス
const FilePath TOWNFIELD_DATA_FILE = U"data/townfield.csv";			// マップデータ
const FilePath BATTLEFIELD_DATA_FILE = U"data/battlefield.csv";		// 戦場データ
const FilePath TILE_STATUS_DATA_FILE = U"data/tilestatus.csv";		// タイルの詳細データ
const FilePath SAVE_DATA_FILE = U"data/savedata.csv";				// セーブデータ
const FilePath TEXT_DATA_FILE = U"data/textdata.csv";				// テキストデータ

// 各ターン定義
enum Turn
{
	PREPARATION,
	PLAYER_TURN,
	ENEMY_TURN,
};
