// NovelScene class

#pragma once

#include  "Common.hpp"

class NovelScene : public App::Scene
{
public:

	// コンストラクタ
	NovelScene(const InitData& init);

	// デストラクタ
	~NovelScene();

	// 更新処理
	void update() override;

	// 描画処理
	void draw() const override;

private:

};
