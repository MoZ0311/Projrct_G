// Stage class

#pragma once

class Stage
{
public:

	// 初期化処理 void(void)
	static void Init();

	// 解放処理 void(void)
	static void Release();

	// 更新処理 void(void)
	void Update();

	// 描画処理 void(void)
	void Draw();

	// インスタンスのゲッター関数
	static Stage* GetStageInstance();

	// テクスチャ配列のゲッター関数
	Array<Texture> GetTileTextureArray();

	// 当たり判定のゲッター関数
	Polygon GetMapCollider();

private:

	// コンストラクタ
	Stage();

	// デストラクタ
	~Stage();

	/// @brief タイルのインデックスから、タイルの底辺中央の座標を計算します。
	/// @param index タイルのインデックス
	/// @param N マップの一辺のタイル数
	/// @return タイルの底辺中央の座標
	Vec2 ToTileBottomCenter(const Point& index, const int32 N);

	/// @brief タイルのインデックスから、タイルの四角形を計算します。
	/// @param index タイルのインデックス
	/// @param N マップの一辺のタイル数
	/// @return タイルの四角形
	Quad ToTile(const Point& index, const int32 N);

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

	// シングルトンクラスのインスタンスのポインタ
	static Stage* stageInstance;

	// タイルのテクスチャ配列
	Array<Texture> tileTextureArray;

	// タイルの一辺の長さ（ピクセル）
	const Vec2 TILE_OFFSET{ 50, 25 };

	// タイルの厚み（ピクセル）
	const int32 TILE_THICKNESS = 15;

	// マップの一辺のタイル数
	const int32 TILE_NUM = 12;

	// 各列の四角形
	const Array<Quad> COLUMN_QUADS = MakeColumnQuads(TILE_NUM);

	// 各行の四角形
	const Array<Quad> ROW_QUADS = MakeRowQuads(TILE_NUM);

	// マップ端の当たり判定用図形
	const Polygon MAP_COLLIDER = Shape2D::Rhombus(TILE_OFFSET.x * 2 * TILE_NUM, TILE_OFFSET.y * 2 * TILE_NUM, Vec2{ 0, TILE_OFFSET.y * TILE_NUM - TILE_THICKNESS - TILE_OFFSET.y * 2});

	// タイルの種類
	Grid<int32> grid;

	// マップ上にカーソルがあるか
	bool onMap = false;

	// マウスカーソルが置かれたタイルのインデックス
	Point mouseOveredTile;

	// マップにグリッドを表示するか
	bool showGrid = false;
};
