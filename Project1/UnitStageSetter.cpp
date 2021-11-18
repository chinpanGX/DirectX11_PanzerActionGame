/*--------------------------------------------------------------
	
	[UnitStageSetter.cpp]
	Author :�@�o���đ�

	���ׂẴX�e�[�W�ɋ��ʂŕK�v�ȃX�e�[�W�I�u�W�F�N�g

---------------------------------------------------------------*/
#include "Scene.h"
#include "Skydome.h"
#include "Plane.h"
#include "UnitStageSetter.h"

/*
	�X�J�C�h�[��
*/
void StageSetterSkydome::Set(Scene * scene)
{
	scene->AddGameObject<Skydome>(LAYER_3D_STAGE);
}

/*
	�n��
*/
void StageSetterPlane::Set(Scene * scene)
{
	scene->AddGameObject<Plane>(LAYER_3D_STAGE);
}
