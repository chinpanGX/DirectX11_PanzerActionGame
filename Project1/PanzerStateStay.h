/*------------------------------------------------------------
	
	[PanzerState.h]
	Author : 出合翔太
	
	何もしないステート

--------------------------------------------------------------*/
#pragma once
#include "PanzerState.h"

class CpuStateRule;
namespace State
{
	
	class Stay final : public PanzerState
	{
	public:
		Stay();
		~Stay();
		void Update(Cpu* pCpu, float deltaTime)override;
	};
}