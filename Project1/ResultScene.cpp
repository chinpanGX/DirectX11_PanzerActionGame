/*-------------------------------------------------
	
	[ResultScene.cpp]
	Author : 出合翔太

--------------------------------------------------*/
#include "Engine.h"
#include "Resource.h"
#include "ResultBg.h"
#include "ResultCommand.h"
#include "GameManager.h"
#include "ResultScene.h"

#pragma region GameScene::Result_method
void GameScene::Result::Init()
{
	// オブジェクトの追加
	AddGameObject<ResultManager>(ELayer::LAYER_SYSTEM);
	AddGameObject<GameBg::ResultUi>(ELayer::LAYER_2D_UI);
	AddGameObject<ResultCommand>(ELayer::LAYER_SYSTEM);
	// リソースのロード
	Load();
	
	// 初期化処理
	Begin();
}

void GameScene::Result::Uninit()
{
	Unload();
	Scene::Uninit();
}

void GameScene::Result::Update()
{
	Scene::Update();
}

void GameScene::Result::Draw()
{
	Scene::Draw();
}

void GameScene::Result::Load()
{
	Engine::Get().resource()->LoadTexture("Ui02", "Ui02.png");
	Engine::Get().resource()->LoadTexture("ResultBg", "ResultBg.png");
	Engine::Get().resource()->AudioLoad("Select", false);
}

void GameScene::Result::Unload()
{
	Engine::Get().resource()->UnloadTexture("ResultBg");
	Engine::Get().resource()->UnloadTexture("Ui02");
	Engine::Get().resource()->AudioUnload();
}
#pragma endregion GameScene::Resultメソッド
