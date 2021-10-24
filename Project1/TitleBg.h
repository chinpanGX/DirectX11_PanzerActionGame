/*-------------------------------------------------
	
	[GameBg.h]
	Author : 出合翔太

--------------------------------------------------*/
#pragma once
#include "GameBg.h"

namespace GameBg
{
	//タイトル背景
	class TitleBg final : public Bg
	{
	public:
		TitleBg();
		~TitleBg();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
	private:
		class TitleSystem* m_TitleSystem = nullptr;
	};
}