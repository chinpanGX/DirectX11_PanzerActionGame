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
	void Set(Scene* Scene)override;
};

// BOX�^�̕�
class GameStageSetterWallBox final : public ISetterObject
{
public:
	void Set(Scene* Scene)override;
};

// �⋋�n�_
class GameStageSetterSupply final : public ISetterObject
{
public:
	void Set(Scene* Scene)override;
};

// ��
class GameStageSetterRock final : public ISetterObject
{
public:
	void Set(Scene* Scene)override;
private:
	void SetBackGround(); // �w�i�p�̊�
	void Set(float x, float y, float z, float size);
	std::vector<D3DXVECTOR3> m_Position;
	std::vector<D3DXVECTOR3> m_Size;
	Scene* m_Scene;
	int32_t m_ObjectCount = 0;
};