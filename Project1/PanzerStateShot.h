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
		void Update(Cpu* pCpu, float deltaTime)override;
	private:
		void PlayAudio(Cpu* pCpu);
		Player* m_Player;
	};
}