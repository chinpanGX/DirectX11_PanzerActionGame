/*--------------------------------------------------------------
	
	[GameStageSetter.h]
	Author : �o���đ�

	�Q�[���X�e�[�W�̃I�u�W�F�N�g��ݒu����

---------------------------------------------------------------*/
#pragma once
#include "ISetterObject.h"

class Scene;
// ��
class GameStageSetterFence final : public ISetterObject
{
public:
	void Set(Scene* scene);
};

// BOX�^�̕�
class GameStageSetterWallBox final : public ISetterObject
{
public:
	void Set(Scene* scene);
};

// �⋋�n�_
class GameStageSetterSupply final : public ISetterObject
{
public:
	void Set(Scene* scene);
};