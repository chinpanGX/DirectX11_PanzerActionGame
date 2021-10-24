/*--------------------------------------------------------------
	
	[GameStage.cpp]
	Author : o‡ãÄ‘¾

---------------------------------------------------------------*/
#include "Engine.h"
#include "Application.h"
#include "UnitStageSetter.h"
#include "GameStageSetter.h"
#include "GameStage.h"

GameStage::GameStage()
{
	m_Scene = Engine::Get().GetApplication()->GetScene();
	Stage::AddObject<StageSetterSkydome>();
	Stage::AddObject<StageSetterPlane>();
	Stage::AddObject<GameStageSetterFence>();
	Stage::AddObject<GameStageSetterWallBox>();
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
