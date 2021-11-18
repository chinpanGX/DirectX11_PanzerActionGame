/*--------------------------------------------------------------
	
	[UnitStageSetter.cpp]
	Author :　出合翔太

	すべてのステージに共通で必要なステージオブジェクト

---------------------------------------------------------------*/
#include "Scene.h"
#include "Skydome.h"
#include "Plane.h"
#include "UnitStageSetter.h"

/*
	スカイドーム
*/
void StageSetterSkydome::Set(Scene * scene)
{
	scene->AddGameObject<Skydome>(LAYER_3D_STAGE);
}

/*
	地面
*/
void StageSetterPlane::Set(Scene * scene)
{
	scene->AddGameObject<Plane>(LAYER_3D_STAGE);
}
