/*--------------------------------------------------------------
	
	[GameStage.cpp]
	Author : 出合翔太

---------------------------------------------------------------*/
#include "Engine.h"
#include "Application.h"
#include "UnitStageSetter.h"
#include "GameStageSetter.h"
#include "GameStage.h"

GameStage::GameStage()
{
	m_Scene = Engine::Get().GetApplication()->GetScene();
	// ステージオブジェクト
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
