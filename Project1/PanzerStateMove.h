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
		void Begin(Player* pPlayer)override;
		void Update(Enemy* pEnemy, float deltaTime)override;
	private:
		int32_t m_Time = 0;
		Player* m_Player;
	};

	class Backward final : public PanzerState
	{
	public:
		Backward();
		~Backward();
		void Begin(Player* pPlayer)override;
		void Update(Enemy* pEnemy, float deltaTime)override;
	};
}