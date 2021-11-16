/*-----------------------------------------------------------
	
	[PanzerStateMove.h]
	Author : �o���đ�

	�ړ�����X�e�[�g

------------------------------------------------------------*/
#pragma once
#include "PanzerState.h"

namespace State
{
	class Forward final : public PanzerState
	{
	public:
		Forward();
		~Forward();
		void Update(Cpu* pCpu, float deltaTime)override;
	};

	class Backward final : public PanzerState
	{
	public:
		Backward();
		~Backward();
		void Update(Cpu* pCpu, float deltaTime)override;
	};
}