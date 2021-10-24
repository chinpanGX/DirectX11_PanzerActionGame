/*--------------------------------------------------------------
	
	[Hp.h]
	Author : 出合翔太

	HPを描画

---------------------------------------------------------------*/
#pragma once
#include "Bg.h"

namespace GameBg
{
	class Hp final : public Actor
	{
	public:
		Hp();
		~Hp();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
	private:
		std::unique_ptr<class Render> m_Render;
		class Player* m_Player;
		const float m_MaxDrawSize = 400.0f; // MAX状態HP

		// プレイヤーのHP
		float m_NowHp = 0.0f; // 現在のHP
		float m_OldHp = 0.0f; // 更新前のHP

		// 描画
		float m_DrawSize = 400.0f; // 現在HP
		float m_DrawRatio = 0.0f; // 描画 比率
		
	};
}

