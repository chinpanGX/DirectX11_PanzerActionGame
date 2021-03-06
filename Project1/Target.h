/*--------------------------------------------------------------
	
	[Target.h]
	Author : 出合翔太

	チュートリアルの的

---------------------------------------------------------------*/
#pragma once
#include "Effect.h"

namespace Billboard
{
	class Target final : public Effect
	{
	public:
		Target();
		~Target();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
	private:
		float m_CoolTime = 100.0f; // 描画しない時間
		bool m_NotDraw = false; // trueで描画しない
	};
}