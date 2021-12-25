/*------------------------------------------------------------ -

	[GameScene.cpp]
	Author : 出合翔太

	ゲームシーンの管理

--------------------------------------------------------------*/
#include "Engine.h"
#include "Resource.h"
#include "Graphics.h"
#include "Application.h"
#include "GameBg.h"
#include "GameCamera.h"
#include "Player.h"
#include "Enemy.h"
#include "SelectCommand.h"
#include "Command.h"
#include "GarageCamera.h"
#include "PanzerGarage.h"
#include "PlaneGarage.h"
#include "PanzerContainer.h"
#include "Pause.h"
#include "GameManager.h"
#include "Gage.h"
#include "Timer.h"
#include "TutorialStage.h"
#include "GameStage.h"
#include "GameScene.h"
#include "PlayerUi.h"
#include "MiniMap.h"
#include "PlayerBulletAmount.h"
#include <thread>

#pragma region GameScene::PanzerSelect_method
void GameScene::PanzerSelect::Init()
{	
	// オブジェクトの追加
	AddGameObject<GarageCamera>(ELayer::LAYER_CAMERA);
	AddGameObject<PlaneGarage>(ELayer::LAYER_3D_STAGE);
	AddGameObject<PanzerGarage>(ELayer::LAYER_3D_STAGE);
	AddGameObject<GameBg::PanzerSelectUi>(ELayer::LAYER_2D_UI);
	AddGameObject<PanzerContainer>(ELayer::LAYER_3D_ACTOR);
	AddGameObject<SelectCommand>(ELayer::LAYER_SYSTEM);
	AddGameObject<GameBg::Mode>(ELayer::LAYER_2D_BG);

	// BGMのロードと再生
	Engine::Get().resource()->AudioLoad("PanzerSelect", true);
	Engine::Get().resource()->AudioPlay("PanzerSelect", 0.6f);

	// リソースのロード
	Load();
	Begin();
}

void GameScene::PanzerSelect::Uninit()
{
	Unload();
	Scene::Uninit();
}

void GameScene::PanzerSelect::Draw()
{
	// ライトの設定
	Light light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(-1.0f, -1.0f, -1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Engine::Get().graphics()->SetLight(light);

	Scene::Draw();

	light.Enable = false;
	Engine::Get().graphics()->SetLight(light);
}

#pragma region private_Fuc
void GameScene::PanzerSelect::Load()
{
	// マルチスレッドでロード
	std::thread thA(&GameScene::PanzerSelect::Thread_Audio, this);
	std::thread thB(&GameScene::PanzerSelect::Thread_Texture_A, this);
	std::thread thC(&GameScene::PanzerSelect::Thread_Texture_B, this);
	std::thread thD(&GameScene::PanzerSelect::Thread_Model, this);

	// 終了まち
	thA.join();
	thB.join();
	thC.join();
	thD.join();
}

void GameScene::PanzerSelect::Unload()
{
	Engine::Get().resource()->UnloadModel("PanzerGarage");
	Engine::Get().resource()->UnloadTexture("Plane");
	Engine::Get().resource()->UnloadTexture("Ui03");
	Engine::Get().resource()->UnloadModel("Param");
	Engine::Get().resource()->UnloadTexture("SelectUi");
	Engine::Get().resource()->UnloadTexture("Waffuru");
	Engine::Get().resource()->UnloadTexture("SelectList");
	Engine::Get().resource()->AudioUnload();
}

void GameScene::PanzerSelect::Thread_Audio()
{
	Engine::Get().resource()->AudioLoad("Select", false);
	Engine::Get().resource()->AudioLoad("Enter", false);
	Engine::Get().resource()->AudioLoad("Cancel", false);
	Engine::Get().resource()->AudioLoad("Button", false);
}

void GameScene::PanzerSelect::Thread_Texture_A()
{
	Engine::Get().resource()->LoadTexture("SelectUi", "SelectUi.png");
	Engine::Get().resource()->LoadTexture("Param", "Parameters.png");
	Engine::Get().resource()->LoadTexture("Waffuru", "waffuru.tif");
}

void GameScene::PanzerSelect::Thread_Texture_B()
{
	Engine::Get().resource()->LoadTexture("Ui03", "Ui03.png");
	Engine::Get().resource()->LoadTexture("Plane", "Plane.dds");	
	Engine::Get().resource()->LoadTexture("SelectList", "psUI.png");
}

void GameScene::PanzerSelect::Thread_Model()
{
	// モデル
	Engine::Get().resource()->LoadModel("PanzerGarage", "souko.obj");
}

#pragma endregion GameScene::PanzerSelectメソッド

#pragma region GameScene::Tutorial_method
void GameScene::Tutorial::Init()
{
	AddGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	AddGameObject<TutorialStage>(ELayer::LAYER_3D_STAGE);
	AddGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	AddGameObject<GameBg::Scope>(ELayer::LAYER_2D_UI);
	AddGameObject<GameCommand>(ELayer::LAYER_SYSTEM);
	AddGameObject<Pause>(ELayer::LAYER_2D_PAUSE);
	AddGameObject<GameBg::TutorialUi>(ELayer::LAYER_2D_UI);
	AddGameObject<PauseCommand>(ELayer::LAYER_SYSTEM);
	AddGameObject<GameManager>(ELayer::LAYER_SYSTEM);
	AddGameObject<PlayerUi::Hp>(ELayer::LAYER_2D_UI);
	AddGameObject<PlayerUi::DrawSkill>(ELayer::LAYER_2D_UI);
	AddGameObject<PlayerUi::Reload>(ELayer::LAYER_2D_UI);
	Load();
	Begin();
}

void GameScene::Tutorial::Uninit()
{
	Unload();
	Scene::Uninit();
}

void GameScene::Tutorial::Update()
{
	Scene::Update();
}

void GameScene::Tutorial::Draw()
{
	// ライトの設定
	Light light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Engine::Get().graphics()->SetLight(light);

	Scene::Draw();

	light.Enable = false;
	Engine::Get().graphics()->SetLight(light);
}

void GameScene::Tutorial::Load()
{
	// オーディオのロード
	Engine::Get().resource()->AudioLoad("Select", false);
	Engine::Get().resource()->AudioLoad("Shot", false);
	Engine::Get().resource()->AudioLoad("Idel", true);
	Engine::Get().resource()->AudioLoad("Skill", false);
	Engine::Get().resource()->AudioLoad("Reload", false);
	// テクスチャのロード
	Engine::Get().resource()->LoadTexture("Target", "Target.png");
	Engine::Get().resource()->LoadTexture("Ui04", "Ui04.png");
	Engine::Get().resource()->LoadTexture("SkillEffect", "Skill.png");
}

void GameScene::Tutorial::Unload()
{
	Engine::Get().resource()->UnloadTexture("SkillEffect");
	Engine::Get().resource()->UnloadTexture("Ui04");
	Engine::Get().resource()->UnloadTexture("Target");
	Engine::Get().resource()->AudioUnload();
}
#pragma endregion private関数
#pragma endregion GameScene::Tutorialメソッド

#pragma region GameScene::Game_method
void GameScene::Game::Init()
{
	AddGameObject<GameCommand>(ELayer::LAYER_SYSTEM);
	AddGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	AddGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	AddGameObject<Enemy>(ELayer::LAYER_3D_ACTOR);
	AddGameObject<GameStage>(ELayer::LAYER_3D_STAGE);
	AddGameObject<GameBg::Scope>(ELayer::LAYER_2D_UI);
	AddGameObject<Pause>(ELayer::LAYER_2D_PAUSE);
	AddGameObject<PauseCommand>(ELayer::LAYER_SYSTEM);
	AddGameObject<GameBg::DrawGage>(ELayer::LAYER_2D_UI);
	AddGameObject<GameManager>(ELayer::LAYER_SYSTEM);
	AddGameObject<GameBg::Timer>(ELayer::LAYER_2D_UI);
	AddGameObject<PlayerUi::Hp>(ELayer::LAYER_2D_UI);
	AddGameObject<PlayerUi::DrawSkill>(ELayer::LAYER_2D_UI);
	AddGameObject<PlayerUi::Reload>(ELayer::LAYER_2D_UI);
	AddGameObject<MiniMap>(ELayer::LAYER_2D_UI);
	AddGameObject<PlayerUi::BulletAmount>(ELayer::LAYER_2D_UI);
	Load();
	Begin();
}

void GameScene::Game::Uninit()
{
	Unload();
	Scene::Uninit();
}

void GameScene::Game::Update()
{
	Scene::Update();
}

void GameScene::Game::Draw()
{
	// ライトの設定
	Light light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Position = D3DXVECTOR4(0.0f, 100.0f, 0.0f, 0.0f);
	light.Ambient = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Engine::Get().graphics()->SetLight(light);

	Scene::Draw();

	light.Enable = false;
	Engine::Get().graphics()->SetLight(light);
}

void GameScene::Game::Load()
{
	// オーディオのロード
	Engine::Get().resource()->AudioLoad("Select", false);
	Engine::Get().resource()->AudioLoad("Idel", true);
	Engine::Get().resource()->AudioLoad("Shot", false);
	Engine::Get().resource()->AudioLoad("Skill", false);
	Engine::Get().resource()->AudioLoad("Reload", false);
	// テクスチャのロード
	Engine::Get().resource()->LoadTexture("SkillEffect", "Skill.png");
	Engine::Get().resource()->LoadTexture("MiniMapBg", "MiniMapBg.dds");
	Engine::Get().resource()->LoadTexture("MiniMapMarker", "MiniMapMarker.png");
	// モデル
	Engine::Get().resource()->LoadModel("Supply", "hokyuu.obj");
}

void GameScene::Game::Unload()
{
	Engine::Get().resource()->AudioUnload();
	Engine::Get().resource()->UnloadTexture("SkillEffect");
	Engine::Get().resource()->UnloadTexture("MiniMapBg");
	Engine::Get().resource()->UnloadTexture("MiniMapMarker");
	Engine::Get().resource()->UnloadModel("Supply");
}

#pragma endregion GameScene::Gameメソッド
