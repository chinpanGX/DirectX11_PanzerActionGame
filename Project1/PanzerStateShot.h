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
		void Begin(Player* Player)override;
		void Update(Enemy* Enemy, float DeltaTime)override;
	private:
		void PlayAudio(Enemy* Enemy);
		Player* m_Player;
	};
}