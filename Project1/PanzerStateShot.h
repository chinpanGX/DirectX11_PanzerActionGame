/*--------------------------------------------------------------
	
	[PanzerStateShot.h]
	Author : 出合翔太

	ステート：撃つ

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