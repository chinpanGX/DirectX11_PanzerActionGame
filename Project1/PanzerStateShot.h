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
		void Begin(Player* Player)override;
		void Update(Enemy* Enemy, float DeltaTime)override;
	private:
		void PlayAudio(Enemy* Enemy);
		Player* m_Player;
	};
}