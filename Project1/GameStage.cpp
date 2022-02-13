/*--------------------------------------------------------------
	
	[GameStage.cpp]
	Author : �o���đ�

---------------------------------------------------------------*/
#include "Engine.h"
#include "Application.h"
#include "UnitStageSetter.h"
#include "GameStageSetter.h"
#include "GameStage.h"

GameStage::GameStage()
{
	m_Scene = Engine::Get().GetApplication()->GetScene();
	// �X�e�[�W�I�u�W�F�N�g
	Stage::AddObject<StageSetterSkydome>();
	Stage::AddObject<StageSetterGameWorld>();
	Stage::AddObject<GameStageSetterFence>();
	Stage::AddObject<GameStageSetterWallBox>();
	Stage::AddObject<GameStageSetterSupply>();
	Stage::AddObject<GameStageSetterRock>();
}

GameStage::~GameStage()
{
	Stage::Remove();
}

void GameStage::Begin()
{
	Stage::AllSet(m_Scene);
}

void GameStage::Update()
{
}

void GameStage::Event()
{
}

void GameStage::Draw()
{
}
