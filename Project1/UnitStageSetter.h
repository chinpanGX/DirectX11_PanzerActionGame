/*--------------------------------------------------------------

	[UintStageSetter.h]
	Author : �o���đ�

	�e�X�e�[�W�ɋ��ʃI�u�W�F�N�g��ݒu����

---------------------------------------------------------------*/
#pragma once
#include "ISetterObject.h"

class Scene;

// �X�J�C�h�[��
class StageSetterSkydome final : public ISetterObject
{
public:
	void Set(Scene* Scene);
};

// �n��
class StageSetterPlane final : public ISetterObject
{
public:
	void Set(Scene* Scene);
};

class StageSetterGameWorld final : public ISetterObject
{
public:
	void Set(Scene* Scene);
};