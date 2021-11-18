/*--------------------------------------------------------------
	
	[GameStageSetter.cpp]
	Author : �o���đ�

---------------------------------------------------------------*/
#include "Scene.h"
#include "Fence.h"
#include "WallBox.h"
#include "GameStageSetter.h"

/*
	��̃I�u�W�F�N�g�̐ݒu����
*/
void GameStageSetterFence::Set(Scene * scene)
{
	for (int32_t i = 0; i < 40; i++)
	{
		// �����̐���
		float x = (float)myLib::Random::Rand_R(-500, 500);
		float z = (float)myLib::Random::Rand_R(-500, 500);
		float angle = (float)myLib::Random::Rand_R(0, 360);
		
		// ���߂���������Transform��ݒ肵�Ă���
		D3DXVECTOR3 pos = D3DXVECTOR3(x, 0.0f, z);
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, angle, 0.0f);

		scene->AddGameObject<Fence>(LAYER_3D_STAGE)->transform().Set(pos, D3DXVECTOR3(1.0f,1.0f,1.0f), rot);
	}
}

/*
	BOX�^�̕�
*/
void GameStageSetterWallBox::Set(Scene * scene)
{
	for (int32_t i = 1; i < 20; ++i)
	{
		// �����̐���
		float random = (float)myLib::Random::Rand_R(3, 10);
		// �T�C�Y�𗐐��Ō��߂�
		D3DXVECTOR3 size = D3DXVECTOR3(random, random, random);

		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(30.0f * i, 0.0f, 150.0f));
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(-30.0f * i, 0.0f, 150.0f));
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(150.0f, 0.0f, -30.0f * i));
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(-150.0f, 0.0f, -30.0f * i));
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(30.0f * i, 0.0f, -150.0f));
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(-30.0f * i, 0.0f, -150.0f));
	}
}
