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
		void Update(Enemy* pEnemy, float deltaTime)override;
	private:
		void PlayAudio(Enemy* pEnemy);
		Player* m_Player;
	};
}