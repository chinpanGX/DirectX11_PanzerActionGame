/*------------------------------------------------------------ -

	[GameScene.cpp]
	Author : �o���đ�

	�Q�[���V�[���̊Ǘ�

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

#pragma region ��ԑI�����
void GameScene::PanzerSelect::Init()
{	
	// �I�u�W�F�N�g�̒ǉ�
	AddGameObject<GarageCamera>(ELayer::LAYER_CAMERA);
	AddGameObject<PlaneGarage>(ELayer::LAYER_3D_STAGE);
	AddGameObject<PanzerGarage>(ELayer::LAYER_3D_STAGE);
	AddGameObject<GameBg::PanzerSelectUi>(ELayer::LAYER_2D_UI);
	AddGameObject<PanzerContainer>(ELayer::LAYER_3D_ACTOR);
	AddGameObject<SelectCommand>(ELayer::LAYER_SYSTEM);
	AddGameObject<GameBg::Mode>(ELayer::LAYER_2D_BG);

	// BGM�̃��[�h�ƍĐ�
	Engine::Get().GetResource()->AudioLoad("PanzerSelect", true);
	Engine::Get().GetResource()->AudioPlay("PanzerSelect", 0.6f);

	// ���\�[�X�̃��[�h
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
	// ���C�g�̐ݒ�
	Light light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(-1.0f, -1.0f, -1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Engine::Get().GetGraphics()->SetLight(light);

	Scene::Draw();

	light.Enable = false;
	Engine::Get().GetGraphics()->SetLight(light);
}

#pragma region private�֐� Load/Unload
void GameScene::PanzerSelect::Load()
{
	// �}���`�X���b�h�Ń��[�h
	std::thread thA(&GameScene::PanzerSelect::Thread_Audio, this);
	std::thread thB(&GameScene::PanzerSelect::Thread_Texture_A, this);
	std::thread thC(&GameScene::PanzerSelect::Thread_Texture_B, this);
	std::thread thD(&GameScene::PanzerSelect::Thread_Model, this);

	// �I���܂�
	thA.join();
	thB.join();
	thC.join();
	thD.join();
}

void GameScene::PanzerSelect::Unload()
{
	Engine::Get().GetResource()->UnloadModel("PanzerGarage");
	Engine::Get().GetResource()->UnloadTexture("Plane");
	Engine::Get().GetResource()->UnloadTexture("Ui03");
	Engine::Get().GetResource()->UnloadModel("Param");
	Engine::Get().GetResource()->UnloadTexture("SelectUi");
	Engine::Get().GetResource()->UnloadTexture("Waffuru");
	Engine::Get().GetResource()->UnloadTexture("SelectList");
	Engine::Get().GetResource()->UnloadTexture("SkillList");
	Engine::Get().GetResource()->UnloadTexture("Ui05");
	Engine::Get().GetResource()->AudioUnload();
}

void GameScene::PanzerSelect::Thread_Audio()
{
	Engine::Get().GetResource()->AudioLoad("Select", false);
	Engine::Get().GetResource()->AudioLoad("Enter", false);
	Engine::Get().GetResource()->AudioLoad("Cancel", false);
	Engine::Get().GetResource()->AudioLoad("Button", false);
}

void GameScene::PanzerSelect::Thread_Texture_A()
{
	Engine::Get().GetResource()->LoadTexture("SelectUi", "SelectUi.png");
	Engine::Get().GetResource()->LoadTexture("ParamBG", "Parameters.png");
	Engine::Get().GetResource()->LoadTexture("Waffuru", "waffuru.tif");
	Engine::Get().GetResource()->LoadTexture("SkillList", "SkillList.png");
}

void GameScene::PanzerSelect::Thread_Texture_B()
{
	Engine::Get().GetResource()->LoadTexture("Ui03", "Ui03.png");
	Engine::Get().GetResource()->LoadTexture("Plane", "Plane.dds");	
	Engine::Get().GetResource()->LoadTexture("SelectList", "psUI.png");
	Engine::Get().GetResource()->LoadTexture("Ui05", "Ui05.png");
}

void GameScene::PanzerSelect::Thread_Model()
{
	// ���f��
	Engine::Get().GetResource()->LoadModel("PanzerGarage", "souko.obj");
}

#pragma endregion GameScene::PanzerSelect���\�b�h

#pragma region �`���[�g���A���V�[��
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
	AddGameObject<PlayerUi::BulletAmount>(ELayer::LAYER_2D_UI);
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
	// ���C�g�̐ݒ�
	Light light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Engine::Get().GetGraphics()->SetLight(light);

	Scene::Draw();

	light.Enable = false;
	Engine::Get().GetGraphics()->SetLight(light);
}

#pragma endregion �`���[�g���A���V�[��

void GameScene::Tutorial::Load()
{
	// �I�[�f�B�I�̃��[�h
	Engine::Get().GetResource()->AudioLoad("Select", false);
	Engine::Get().GetResource()->AudioLoad("Shot", false);
	Engine::Get().GetResource()->AudioLoad("Idel", true);
	Engine::Get().GetResource()->AudioLoad("Skill", false);
	Engine::Get().GetResource()->AudioLoad("Reload", false);
	// �e�N�X�`���̃��[�h
	Engine::Get().GetResource()->LoadTexture("Target", "Target.png");
	Engine::Get().GetResource()->LoadTexture("Ui04", "Ui04.png");
	Engine::Get().GetResource()->LoadTexture("SkillEffect", "Skill.png");
	// ���f���̃��[�h
	Engine::Get().GetResource()->LoadModel("Supply", "hokyuu.obj");
}

void GameScene::Tutorial::Unload()
{
	Engine::Get().GetResource()->UnloadModel("Supply");
	Engine::Get().GetResource()->UnloadTexture("SkillEffect");
	Engine::Get().GetResource()->UnloadTexture("Ui04");
	Engine::Get().GetResource()->UnloadTexture("Target");
	Engine::Get().GetResource()->AudioUnload();
}


#pragma region �Q�[���V�[��
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
	// ���C�g�̐ݒ�
	Light light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Position = D3DXVECTOR4(0.0f, 100.0f, 0.0f, 0.0f);
	light.Ambient = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Engine::Get().GetGraphics()->SetLight(light);

	Scene::Draw();

	light.Enable = false;
	Engine::Get().GetGraphics()->SetLight(light);
}

#pragma region private�֐� Load/Unload
void GameScene::Game::Load()
{
	// �}���`�X���b�h�Ń��[�h
	std::thread thA(&GameScene::Game::Thread_Audio, this);
	std::thread thB(&GameScene::Game::Thread_Texture, this);
	std::thread thC(&GameScene::Game::Thread_ModelA, this);
	std::thread thD(&GameScene::Game::Thread_ModelB, this);

	// �I���܂�
	thA.join();
	thB.join();
	thC.join();
	thD.join();
}

void GameScene::Game::Thread_Audio()
{
	// �I�[�f�B�I�̃��[�h
	Engine::Get().GetResource()->AudioLoad("Select", false);
	Engine::Get().GetResource()->AudioLoad("Idel", true);
	Engine::Get().GetResource()->AudioLoad("Shot", false);
	Engine::Get().GetResource()->AudioLoad("Skill", false);
	Engine::Get().GetResource()->AudioLoad("Reload", false);
}

void GameScene::Game::Thread_Texture()
{
	// �e�N�X�`���̃��[�h
	Engine::Get().GetResource()->LoadTexture("SkillEffect", "Skill.png");
	Engine::Get().GetResource()->LoadTexture("MiniMapBg", "MiniMapBg.dds");
	Engine::Get().GetResource()->LoadTexture("MiniMapMarker", "MiniMapMarker.png");
}

void GameScene::Game::Thread_ModelA()
{
	Engine::Get().GetResource()->LoadModel("Supply", "hokyuu.obj");
	Engine::Get().GetResource()->LoadModel("Rock_01", "Rock_01.obj");
	Engine::Get().GetResource()->LoadModel("Rock_02", "Rock_02.obj");
	Engine::Get().GetResource()->LoadModel("Rock_03", "Rock_03.obj");
}

void GameScene::Game::Thread_ModelB()
{
	Engine::Get().GetResource()->LoadModel("Rock02_01", "Rock02_01.obj");
	Engine::Get().GetResource()->LoadModel("Rock02_02", "Rock02_02.obj");
	Engine::Get().GetResource()->LoadModel("Rock02_03", "Rock02_03.obj");
	//Engine::Get().GetResource()->LoadModel("Rock03_01", "HalfRock_01.obj");
	//Engine::Get().GetResource()->LoadModel("Rock03_02", "HalfRock_02.obj");
	//Engine::Get().GetResource()->LoadModel("Rock03_03", "HalfRock_03.obj");
}

void GameScene::Game::Unload()
{
	Engine::Get().GetResource()->AudioUnload();
	Engine::Get().GetResource()->UnloadTexture("SkillEffect");
	Engine::Get().GetResource()->UnloadTexture("MiniMapBg");
	Engine::Get().GetResource()->UnloadTexture("MiniMapMarker");
	Engine::Get().GetResource()->UnloadModel("Supply");
	Engine::Get().GetResource()->UnloadModel("Rock_01");
	Engine::Get().GetResource()->UnloadModel("Rock_02");
	Engine::Get().GetResource()->UnloadModel("Rock_03");
	Engine::Get().GetResource()->UnloadModel("Rock02_01");
	Engine::Get().GetResource()->UnloadModel("Rock02_02");
	Engine::Get().GetResource()->UnloadModel("Rock02_03");
	//Engine::Get().GetResource()->UnloadModel("Rock03_01");
	//Engine::Get().GetResource()->UnloadModel("Rock03_02");
	//Engine::Get().GetResource()->UnloadModel("Rock03_03");
}
#pragma endregion private�֐�
#pragma endregion GameScene::Game���\�b�h
