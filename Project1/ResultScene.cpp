/*-------------------------------------------------
	
	[ResultScene.cpp]
	Author : �o���đ�

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
	// �I�u�W�F�N�g�̒ǉ�
	AddGameObject<ResultManager>(ELayer::LAYER_SYSTEM);
	AddGameObject<GameBg::ResultUi>(ELayer::LAYER_2D_UI);
	AddGameObject<ResultCommand>(ELayer::LAYER_SYSTEM);
	// ���\�[�X�̃��[�h
	Load();
	
	// ����������
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
#pragma endregion GameScene::Result���\�b�h
