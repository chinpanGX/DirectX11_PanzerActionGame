/*--------------------------------------------------------------

	[TutorialStageSetter.cpp]
	Author : �o���đ�

	�`���[�g���A���X�e�[�W�̃I�u�W�F�N�g��ݒu����

---------------------------------------------------------------*/
#include "Scene.h"
#include "WallBox.h"
#include "Target.h"
#include "Supply.h"
#include "TutorialStageSetter.h"

/*
	BOX�^�̕�
 */
void TutorialStageSetterWall::Set(Scene * scene)
{
	// �T�C�Y�̐ݒ�
	D3DXVECTOR3 size = D3DXVECTOR3(3.0f, 3.0f, 3.0f);

	// GameObject�̃��X�g�ɒǉ�
	for (int32_t i = 0; i < 20; ++i)
	{
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(8.0f * i, 0.0f, 0.0f), size, g_NegUnitZ);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(-8.0f * i, 0.0f, 0.0f), size, g_NegUnitZ);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(150.0f, 0.0f, -12.0f * i), size, g_NegUnitX);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(-150.0f, 0.0f, -12.0f * i), size, g_UnitX);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(8.0f * i, 0.0f, -200.0f), size, g_UnitZ);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(-8.0f * i, 0.0f, -200.0f), size, g_UnitZ);
	}
}

/*
	�I�̃I�u�W�F�N�g
*/
void TutorialStageSetterTarget::Set(Scene * scene)
{
	// GameObject�̃��X�g�ɒǉ�->�ʒu�̐ݒ�
	scene->AddGameObject<Target>(LAYER_2D_EFFECT)->transform().position(0.0f, 10.0f, 150.0f);
	for (int32_t i = 1; i < 3; ++i)
	{
		scene->AddGameObject<Target>(LAYER_2D_EFFECT)->transform().position(40.0f * i, 5.0f, 100.0f);
		scene->AddGameObject<Target>(LAYER_2D_EFFECT)->transform().position(-40.0f * i, 5.0f, 100.0f);
		scene->AddGameObject<Target>(LAYER_2D_EFFECT)->transform().position(40.0f * i, 25.0f, 200.0f);
		scene->AddGameObject<Target>(LAYER_2D_EFFECT)->transform().position(-40.0f * i, 25.0f, 200.0f);
	}
}

void TutorialStageSetterSupply::Set(Scene * scene)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(30.0f, 0.0f, -100.0f);
	D3DXVECTOR3 scl = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, -0.2f, 0.0f);

	scene->AddGameObject<Supply>(LAYER_3D_STAGE)->transform().Set(pos, scl, rot);
}
