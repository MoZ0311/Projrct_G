// Stage class

#include "Stage.hpp"

// インスタンスをnullptrで初期化
Stage* Stage::stageInstance = nullptr;

Stage::Stage()
{

}

Stage::~Stage()
{

}

void Stage::Init()
{
	if (stageInstance != nullptr)
	{
		return;
	}

	stageInstance = new Stage();
}

void Stage::Release()
{
	if (stageInstance != nullptr)
	{
		delete stageInstance;
		stageInstance = nullptr;
	}
}

void Stage::Update()
{
	if (KeySpace.down())
	{
		Print << U"押された!!";
	}

	if (KeySpace.up())
	{
		ClearPrint();
	}
}


void Stage::Draw()
{

}

Stage* Stage::GetStageInstance()
{
	return stageInstance;
}
