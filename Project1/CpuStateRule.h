/*-------------------------------------------------------------

	[CpuStateRule.h]
	CPU�̓����̃��[���A�������`���ĊǗ�����
	Author : �o���đ�

--------------------------------------------------------------*/
#pragma once
#include "stdafx.h"

class CpuStateRule
{
public:
	CpuStateRule();
	~CpuStateRule();
	
	//�@���������߂�
	void DecideBehavior();

	// �G�l�~�[�ƃv���C���[�̋����𑪂�
	void PlayerToDistance(class Cpu* Cpu);

	// 
	const int32_t behavior() const;
private:
	int32_t m_Behavior; // ���ė~��������������
	float m_PlayerToDistance; // �v���C���[�Ƃ̋���


	const float m_SearchRange = 200.0f; // �T�[�`�͈�
	const float m_ShotRange = 50.0f;	// �˒��͈�
};

