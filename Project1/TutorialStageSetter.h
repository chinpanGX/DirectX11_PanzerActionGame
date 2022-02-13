/*--------------------------------------------------------------

	[TutorialStageSetter.h]
	Author : �o���đ�

	�`���[�g���A���X�e�[�W�̃I�u�W�F�N�g��ݒu����

---------------------------------------------------------------*/
#pragma once
#include "ISetterObject.h"

class Scene;

// �ǂ̐ݒu
class TutorialStageSetterWall final : public ISetterObject
{
public:
	void Set(Scene* Scene)override;
};

// �I�̐ݒu
class TutorialStageSetterTarget final : public ISetterObject
{
public:
	void Set(Scene* Scene)override;
};

class TutorialStageSetterSupply final : public ISetterObject
{
public:
	void Set(Scene* Scene)override;
};