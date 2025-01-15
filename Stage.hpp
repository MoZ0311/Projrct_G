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
	const Vec2 TileOffset{ 50, 25 };

	// タイルの厚み（ピクセル）
	const int32 TileThickness = 15;

	// マップの一辺のタイル数
	const int32 N = 12;

	// 各列の四角形
	const Array<Quad> columnQuads = MakeColumnQuads(N);

	// 各行の四角形
	const Array<Quad> rowQuads = MakeRowQuads(N);

	// タイルの種類
	Grid<int32> grid;

	// タイルメニューで選択されているタイルの種類
	int32 tileTypeSelected = 30;

	// タイルメニューの四角形
	const RoundRect TileMenuRoundRect = RectF{ 20, 20, (56 * 22), (50 * 4) }.stretched(10).rounded(8);

	// マップにグリッドを表示するか
	bool showGrid = false;
};
