/*-----------------------------------------------------------
	
	[PanzerStateMove.h]
	Author : 出合翔太

	移動するステート

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