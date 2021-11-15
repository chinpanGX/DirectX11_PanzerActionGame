/*-------------------------------------------------
	
	[ResultBg.h]
	Author : 出合翔太

--------------------------------------------------*/
#pragma once
#include "Bg.h"

class Renderer2D;
namespace GameBg
{
	// リザルト背景
	class ResultBg final : public Bg
	{
	public:
		ResultBg();
		~ResultBg();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
		void Begin(bool winner);
		class ResultState& GetState() const;
	private:
		std::unique_ptr<Renderer2D> m_Fade;
		std::unique_ptr<class ResultState>m_State;
		int32_t m_Count;
		float m_Alpha;
		bool m_flag;
	};

	// リザルトUI
	class ResultUi final : public Bg
	{
	public:
		ResultUi();
		~ResultUi();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
	private:
		std::unique_ptr<Renderer2D> m_Marker; // 選択マーカー
		float m_Draw_y;
		float m_Alpha;
	};
}