/*------------------------------------------------------------
	
	[PanzerState.h]
	Author : �o���đ�
	
	�������Ȃ��X�e�[�g

--------------------------------------------------------------*/
#pragma once
#include "PanzerState.h"

class Player;
namespace State
{	
	class Stay final : public PanzerState
	{
	public:
		Stay();
		~Stay();
		void Update(Cpu* pCpu, float deltaTime)override;
	private:
		Player* m_Player;

		float m_PlayerToDistance; // �v���C���[�Ƃ̋��� 
		const float m_SearchRange = 500.0f; // �T�[�`�͈�
		const float m_ShotRange = 200.0f;	// �˒��͈�
	};
}