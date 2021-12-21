/*-----------------------------------------------------------
	
	[PanzerUseSkill.h]
	Author : 出合翔太
	スキルを使う

------------------------------------------------------------*/
#pragma once
#include "PanzerState.h"

namespace State
{
	class UseSkill final : public PanzerState
	{
	public:
		UseSkill();
		~UseSkill();
		void Begin(Player* pPlayer)override;
		void Update(Enemy* pEnemy, float deltaTime)override;
	};
}

