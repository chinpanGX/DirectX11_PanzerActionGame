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
		Math::Vector3 pos = Math::Vector3(x, 0.0f, z);
		Math::Quaternion rot = Math::Quaternion(Math::Vector3::UnitY, angle);
		scene->AddGameObject<Fence>(LAYER_3D_STAGE)->transform().Set(pos, Math::Vector3::One, rot);
	}
}

void GameStageSetterWallBox::Set(Scene * scene)
{
	for (int32_t i = 1; i < 20; ++i)
	{
		float random = (float)myLib::Random::Rand_R(3, 10);
		Math::Vector3 size = Math::Vector3(random, random, random);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(Math::Vector3(30.0f * i, 0.0f, 150.0f), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(Math::Vector3(-30.0f * i, 0.0f, 150.0f), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(Math::Vector3(150.0f, 0.0f, -30.0f * i), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(Math::Vector3(-150.0f, 0.0f, -30.0f * i), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(Math::Vector3(30.0f * i, 0.0f, -150.0f), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(Math::Vector3(-30.0f * i, 0.0f, -150.0f), size);
	}
}
