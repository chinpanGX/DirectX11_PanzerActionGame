/*--------------------------------------------------------------
	
	[GameStageSetterFence.cpp]
	Author : èoçá„ƒëæ

---------------------------------------------------------------*/
#include "Scene.h"
#include "Fence.h"
#include "WallBox.h"
#include "GameStageSetter.h"

void GameStageSetterFence::Set(Scene * scene)
{
	for (int32_t i = 0; i < 40; i++)
	{
		float x = (float)myLib::Random::Rand_R(-500, 500);
		float z = (float)myLib::Random::Rand_R(-500, 500);
		float angle = (float)myLib::Random::Rand_R(0, 360);
		D3DXVECTOR3 pos = D3DXVECTOR3(x, 0.0f, z);
		scene->AddGameObject<Fence>(LAYER_3D_STAGE)->transform().Set(pos, D3DXVECTOR3(1.0f,1.0f,1.0f));
	}
}

void GameStageSetterWallBox::Set(Scene * scene)
{
	for (int32_t i = 1; i < 20; ++i)
	{
		float random = (float)myLib::Random::Rand_R(3, 10);
		D3DXVECTOR3 size = D3DXVECTOR3(random, random, random);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(D3DXVECTOR3(30.0f * i, 0.0f, 150.0f), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(D3DXVECTOR3(-30.0f * i, 0.0f, 150.0f), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(D3DXVECTOR3(150.0f, 0.0f, -30.0f * i), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(D3DXVECTOR3(-150.0f, 0.0f, -30.0f * i), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(D3DXVECTOR3(30.0f * i, 0.0f, -150.0f), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(D3DXVECTOR3(-30.0f * i, 0.0f, -150.0f), size);
	}
}
