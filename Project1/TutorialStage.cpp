/*--------------------------------------------------------------

	[TutorialSatge.h]
	Author : �o���đ�

	�`���[�g���A���X�e�[�W���쐬����

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
	m_Scene = Engine::Get().application()->GetScene();
	// �X�e�[�W�̃I�u�W�F�N�g�����X�g�ɒǉ�
	Stage::AddObject<StageSetterSkydome>();
	Stage::AddObject<StageSetterPlane>();
	Stage::AddObject<TutorialStageSetterTarget>();
	Stage::AddObject<TutorialStageSetterWall>();
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
#pragma endregion TutorialStage���\�b�h