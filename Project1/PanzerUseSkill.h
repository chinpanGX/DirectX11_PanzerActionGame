/*-----------------------------------------------------------
	
	[PanzerUseSkill.h]
	Author : �o���đ�
	�X�L�����g��

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
		void Update(class Cpu* pCpu, float deltaTime)override;
	};
}

