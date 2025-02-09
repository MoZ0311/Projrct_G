// MapBase class

#pragma once

#include "Common.hpp"

class MapBase
{
public:

	// コンストラクタ
	MapBase();

	// デストラクタ
	~MapBase();

	// 更新処理
	virtual void Update();

	// 描画処理
	void Draw();

	// CSVのデータと現在のマップデータが同一かの判定処理
	bool MapEqualsCSV();

	// タイルのテクスチャ配列のゲッター関数
	Array<Texture> GetTileTextureArray();

	/// @brief タイルのインデックスから、タイルの底辺中央の座標を計算します。
	/// @param index タイルのインデックス
	/// @param N マップの一辺のタイル数
	/// @return タイルの底辺中央の座標
	Vec2 ToTileBottomCenter(const Point& index, const int32 N) const;

	// タイルの一辺の長さ（ピクセル）
	const Vec2 TILE_OFFSET{ 48, 24 };

	// タイルの厚み（ピクセル）
	const int32 TILE_THICKNESS = 17;

protected:

	// マップデータのセーブ処理
	virtual void SaveMapData();

	// タイルの強調表示処理
	virtual void DrawTileHighlight();

	// グリッドの描画処理
	virtual void DrawGrid();	

	/// @brief タイルのインデックスから、タイルの四角形を計算します。
	/// @param index タイルのインデックス
	/// @param N マップの一辺のタイル数
	/// @return タイルの四角形
	Quad ToTile(const Point& index, const int32 N) const;

	/// @brief 指定した列のタイルによって構成される四角形を計算します。
	/// @param x 列インデックス
	/// @param N マップの一辺のタイル数
	/// @return 指定した列のタイルによって構成される四角形
	Quad ToColumnQuad(const int32 x, const int32 N);

	/// @brief 指定した行のタイルによって構成される四角形を計算します。
	/// @param y 行インデックス
	/// @param N マップの一辺のタイル数
	/// @return 指定した行のタイルによって構成される四角形
	Quad ToRowQuad(const int32 y, const int32 N);

	/// @brief 各列のタイルによって構成される四角形の配列を作成します。
	/// @param N マップの一辺のタイル数
	/// @return 各列のタイルによって構成される四角形の配列
	Array<Quad> MakeColumnQuads(const int32 N);

	/// @brief 各行のタイルによって構成される四角形の配列を作成します。
	/// @param N マップの一辺のタイル数
	/// @return 各行のタイルによって構成される四角形の配列
	Array<Quad> MakeRowQuads(const int32 N);

	/// @brief 指定した座標にあるタイルのインデックスを返します。
	/// @param pos 座標
	/// @param columnQuads 各列のタイルによって構成される四角形の配列
	/// @param rowQuads 各行のタイルによって構成される四角形の配列
	/// @return タイルのインデックス。指定した座標にタイルが無い場合は none
	Optional<Point> ToIndex(const Vec2& pos, const Array<Quad>& columnQuads, const Array<Quad>& rowQuads);

	/// @brief 画像を読み込み、アルファ乗算済みのテクスチャを作成します。
	/// @param path 画像ファイルのパス
	/// @return アルファ乗算済みのテクスチャ
	/// @remark 境界付近の品質を向上させるため、アルファ乗算済みのテクスチャを作成します。
	/// @remark 描画時は `BlendState::Premultiplied` を指定してください。
	Texture LoadPremultipliedTexture(FilePathView path);

	// マップの一辺のタイル数
	int32 tileNum;

	// タイルのテクスチャ配列
	Array<Texture> tileTextureArray;

	// 各列の四角形
	Array<Quad> columnQuadArray;

	// 各行の四角形
	Array<Quad> rowQuadArray;

	// マップ配置のCSVファイル
	CSV mapData;

	// 各タイルのステータスのCSVファイル
	CSV tileStatus;

	// タイルの種類
	Grid<int32> grid;

	// マップ上にカーソルがあるか
	bool onMap;

	// マウスカーソルが置かれたタイルのインデックス
	Point mouseOveredTile;
};
