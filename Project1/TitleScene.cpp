/*-------------------------------------------------
	
	[TitleScene.cpp]
	Author : 出合翔太

--------------------------------------------------*/
#include "Engine.h"
#include "Resource.h"
#include "TitleBg.h"
#include "TitleSystem.h"
#include "TitleCommand.h"
#include "TitleScene.h"
#include <thread>

#pragma region GameScene::Title_method
void GameScene::Title::Init()
{
	// オブジェクトの追加
	TitleSystem* titlesystem = AddGameObject<TitleSystem>(ELayer::LAYER_2D_UI);
	AddGameObject<GameBg::TitleBg>(ELayer::LAYER_2D_BG)->titleSystem(titlesystem);

	for (int32_t i = 0; i < 100; i++)
	{
		AddGameObject<Particle>(ELayer::LAYER_2D_BG)->titleSystem(titlesystem);
	}
	AddGameObject<TitleCommand>(ELayer::LAYER_SYSTEM);
	
	// リソースのロード
	Load();
	Engine::Get().resource()->AudioPlay("Title", 0.3f);

	Begin();
}

void GameScene::Title::Uninit()
{
	Unload();
	Scene::Uninit();
}

void GameScene::Title::Update()
{
	Scene::Update();
}

void GameScene::Title::Draw()
{
	Scene::Draw();
}

void GameScene::Title::Load()
{
	// テクスチャ
	Engine::Get().resource()->LoadTexture("TitleBg", "TitleBg.png");

	// オーディオ
	Engine::Get().resource()->AudioLoad("Title", true);
	Engine::Get().resource()->AudioLoad("Button", false);
	Engine::Get().resource()->AudioLoad("Enter", false);
	Engine::Get().resource()->AudioLoad("Cancel", false);
	Engine::Get().resource()->AudioLoad("Select", false);
}

void GameScene::Title::Unload()
{
	Engine::Get().resource()->UnloadTexture("TitleBg");
	Engine::Get().resource()->AudioUnload();
}
#pragma endregion GameScene::Titleメソッド
