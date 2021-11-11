/*--------------------------------------------------------------

	[TutorialStageSetter.cpp]
	Author : o‡ãÄ‘¾

---------------------------------------------------------------*/
#include "Scene.h"
#include "WallBox.h"
#include "Target.h"
#include "TutorialStageSetter.h"

// •Ç
void TutorialStageSetterWall::Set(Scene * scene)
{
	Math::Vector3 size = Math::Vector3(3.0f, 3.0f, 3.0f);
	scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(Math::Vector3(0.0f, 0.0f, 0.0f), size);
	scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(Math::Vector3(0.0f, 0.0f, -80.0f), size);
	scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(Math::Vector3(0.0f, 0.0f, -200.0f), size);
	for (int32_t i = 1; i < 20; ++i)
	{
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(Math::Vector3(12.0f * i, 0.0f, 0.0f), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(Math::Vector3(-12.0f * i, 0.0f, 0.0f), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(Math::Vector3(12.0f * i, 0.0f, -120.0f), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(Math::Vector3(-12.0f * i, 0.0f, -120.0f), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(Math::Vector3(150.0f, 0.0f, -12.0f * i), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(Math::Vector3(-150.0f, 0.0f, -12.0f * i), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(Math::Vector3(12.0f * i, 0.0f, -200.0f), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->transform().Set(Math::Vector3(-12.0f * i, 0.0f, -200.0f), size);
	}
}

// “I
void TutorialStageSetterTarget::Set(Scene * scene)
{
	scene->AddGameObject<Target>(LAYER_2D_EFFECT)->transform().position(0.0f, 10.0f, 150.0f);
	for (int32_t i = 1; i < 3; ++i)
	{
		scene->AddGameObject<Target>(LAYER_2D_EFFECT)->transform().position(40.0f * i, 5.0f, 100.0f);
		scene->AddGameObject<Target>(LAYER_2D_EFFECT)->transform().position(-40.0f * i, 5.0f, 100.0f);
		scene->AddGameObject<Target>(LAYER_2D_EFFECT)->transform().position(40.0f * i, 25.0f, 200.0f);
		scene->AddGameObject<Target>(LAYER_2D_EFFECT)->transform().position(-40.0f * i, 25.0f, 200.0f);
	}
}
