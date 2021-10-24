/*--------------------------------------------------------------
	
	[UnitStageSetter.cpp]
	Author :@o‡ãÄ‘¾

---------------------------------------------------------------*/
#include "Scene.h"
#include "Skydome.h"
#include "Plane.h"
#include "UnitStageSetter.h"

void StageSetterSkydome::Set(Scene * scene)
{
	scene->AddGameObject<Skydome>(LAYER_3D_STAGE);
}

void StageSetterPlane::Set(Scene * scene)
{
	scene->AddGameObject<Plane>(LAYER_3D_STAGE);
}
