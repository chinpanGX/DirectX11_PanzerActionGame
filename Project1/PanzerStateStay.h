/*------------------------------------------------------------
	
	[PanzerState.h]
	Author : �o���đ�
	
	�������Ȃ��X�e�[�g

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