/*-------------------------------------------------------------

	[CpuStateRule.h]
	CPU�̓����̃��[���A�������`���ĊǗ�����
	Author : �o���đ�

--------------------------------------------------------------*/
#pragma once
#include "stdafx.h"

class Cpu;
class CpuStateRule
{
public:
	CpuStateRule() = delete;
	CpuStateRule(Cpu* pCpu);
	~CpuStateRule();
	// �X�V����
	void Update();

	// 
	const int32_t behavior() const;
private:
	// �G�l�~�[�ƃv���C���[�̋����𑪂�
	void PlayerToDistance();
	
	//�@���������߂�
	void DecideBehavior();
	
	int32_t m_Behavior; // ���ė~��������������
	float m_PlayerToDistance; // �v���C���[�Ƃ̋���

	const float m_SearchRange = 50000.0f; // �T�[�`�͈�
	const float m_ShotRange = 25000.0f;	// �˒��͈�

	Cpu* m_Cpu = nullptr;
};

