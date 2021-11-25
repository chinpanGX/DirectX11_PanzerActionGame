/*-----------------------------------------------------------
	
	[PanzerStateMove.h]
	Author : �o���đ�

	�ړ�����X�e�[�g

------------------------------------------------------------*/
#pragma once
#include "PanzerState.h"

class Player;
namespace State
{
	class Forward final : public PanzerState
	{
	public:
		Forward();
		~Forward();
		void Update(Cpu* pCpu, float deltaTime)override;
	private:
		float m_Time = 0.0f;
		Player* m_Player;
	};

	class Backward final : public PanzerState
	{
	public:
		Backward();
		~Backward();
		void Update(Cpu* pCpu, float deltaTime)override;
	};
}