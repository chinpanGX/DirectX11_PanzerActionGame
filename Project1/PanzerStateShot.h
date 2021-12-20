/*--------------------------------------------------------------
	
	[PanzerStateShot.h]
	Author : �o���đ�

	�X�e�[�g�F����

----------------------------------------------------------------*/
#pragma once
#include "PanzerState.h"

class Player;
namespace State
{
	class Shot final : public PanzerState
	{
	public:
		Shot();
		~Shot();
		void Begin(Player* pPlayer)override;
		void Update(Enemy* pEnemy, float deltaTime)override;
	private:
		void PlayAudio(Enemy* pEnemy);
		Player* m_Player;
	};
}