/*-----------------------------------------------------------
	
	[PanzerStateMove.h]
	Author : 出合翔太

	移動するステート

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
		void Begin(Player* Player)override;
		void Update(Enemy* Enemy, float DeltaTime)override;
	private:
		int32_t m_Time = 0;
		Player* m_Player;
	};

	class Backward final : public PanzerState
	{
	public:
		Backward();
		~Backward();
		void Begin(Player* Player)override;
		void Update(Enemy* Enemy, float DeltaTime)override;
	};
}