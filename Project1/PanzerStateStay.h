/*------------------------------------------------------------
	
	[PanzerState.h]
	Author : 出合翔太
	
	何もしないステート

--------------------------------------------------------------*/
#pragma once
#include "PanzerState.h"

class Player;
namespace State
{	
	class Stay final : public PanzerState
	{
	public:
		Stay();
		~Stay();
		void Begin(Player* Player)override;
		void Update(Enemy* Enemy, float DeltaTime)override;
	private:
		Player* m_Player;

		float m_PlayerToDistance; // プレイヤーとの距離 
		const float m_SearchRange = 500.0f; // サーチ範囲
		const float m_ShotRange = 300.0f;	// 射程範囲
	};
}

// ターゲットが左右どちらにいるかを調べる
float FindTargetDirection(Player* target, Enemy* Enemy, const D3DXVECTOR3& forward);
