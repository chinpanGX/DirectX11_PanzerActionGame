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
		void Begin(Player* pPlayer)override;
		void Update(Enemy* pEnemy, float deltaTime)override;
	private:
		Player* m_Player;

		float m_PlayerToDistance; // �v���C���[�Ƃ̋��� 
		const float m_SearchRange = 500.0f; // �T�[�`�͈�
		const float m_ShotRange = 300.0f;	// �˒��͈�
	};
}

// �^�[�Q�b�g�����E�ǂ���ɂ��邩�𒲂ׂ�
float FindTargetDirection(Player* target, Enemy* pEnemy, const D3DXVECTOR3& forward);
