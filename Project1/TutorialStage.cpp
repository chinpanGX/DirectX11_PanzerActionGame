/*--------------------------------------------------------------

	[TutorialSatge.h]
	Author : 出合翔太

	チュートリアルステージを作成する

---------------------------------------------------------------*/
#include "Engine.h"
#include "Application.h"
#include "Scene.h"
#include "UnitStageSetter.h"
#include "TutorialStageSetter.h"
#include "TutorialStage.h"

#pragma region TutorialStage_method
TutorialStage::TutorialStage()
{
	m_Scene = Engine::Get().GetApplication()->GetScene();
	// ステージのオブジェクトをリストに追加
	Stage::AddObject<StageSetterSkydome>();
	Stage::AddObject<StageSetterPlane>();
	Stage::AddObject<TutorialStageSetterTarget>();
	Stage::AddObject<TutorialStageSetterWall>();
	Stage::AddObject<TutorialStageSetterSupply>();
}

TutorialStage::~TutorialStage()
{
	Stage::Remove();
}

void TutorialStage::Begin()
{
	Stage::AllSet(m_Scene);
}

void TutorialStage::Update()
{
}

void TutorialStage::Event()
{
}

void TutorialStage::Draw()
{
}
#pragma endregion TutorialStageメソッド