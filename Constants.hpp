// 定数定義

#pragma once

constexpr int32 SCREEN_WIDTH = 1366;					// 画面の幅
constexpr int32 SCREEN_HEIGHT = 768;					// 画面の高さ

// アセット用定数
const String FONT_MAKINAS = U"MAKINAS";					// Makinasフォント

const String PLAYER_BASE = U"PlayerBase";				// プレイヤー基本画像
const String PLAYER_IDOL = U"PlayerIdol";				// プレイヤー待機画像
const String PLAYER_WALK_01 = U"PlayerWalk_01";			// プレイヤー歩行画像01
const String PLAYER_WALK_02 = U"PlayerWalk_02";			// プレイヤー歩行画像02

const String RANGER_RED_BASE = U"RangerRedBase";		// レッド基本画像

// CSVファイルのパス
const FilePath MAP_DATA_FILE = U"data/mapdata.csv";		// マップデータ
const FilePath SAVE_DATA_FILE = U"data/savedata.csv";	// セーブデータ
const FilePath TEXT_DATA_FILE = U"data/textdata.csv";	// テキストデータ

// 各ターン定義
enum Turn
{
	PREPARATION,
	PLAYER_TURN,
	ENEMY_TURN,
};
