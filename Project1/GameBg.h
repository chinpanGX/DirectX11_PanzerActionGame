/*------------------------------------------------------------

	[GameBg.h]
	Author : 出合翔太

	ゲームの2D背景

-------------------------------------------------------------*/
#pragma once
#include "Bg.h"
#include <array>
#include <vector>

class Renderer2D;
namespace GameBg
{
	// スコープ
	class Scope final : public Bg
	{
	public:
		Scope();
		~Scope();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
	};

	// 選択画面背景UI
	class PanzerSelectUi final : public Bg
	{
	public:
		PanzerSelectUi();
		~PanzerSelectUi();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
		void Down();
		void Up();
		void Enable();
		void Disable();
		const bool GetDrawFlag() const;
	private:
		// 描画
		void DrawPanzerName();	// 戦車の名前
		void DrawGameRule(D3DXVECTOR2 pos, D3DXVECTOR2 size);	// ゲーム説明	

		std::vector<D3DXVECTOR2> m_TexCoord;
		std::unique_ptr<Renderer2D> m_List; // 戦車のリスト
		std::unique_ptr<Renderer2D> m_Operation; // 操作方法UI
		int32_t m_Page;
		bool m_DrawFlag = false;
	};

	// モード選択
	class Mode final : public Bg
	{
	public:
		Mode();
		~Mode();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
		bool SetMode(bool f); 
	private:		
		// 描画
		void DrawFrame(D3DXVECTOR2 pos, float size_y);	// 背景枠の点滅
		void DrawModeName(D3DXVECTOR2 pos, float size_y);	// ゲームモード

		std::unique_ptr<Renderer2D> m_Renderer;
		bool m_Mode; // trueでチュートリアル、falseでゲーム
		float m_Alpha = 1.0f;
		float m_Color = 0.01f;
	};

	// チュートリアルの操作説明
	class TutorialUi final : public Bg
	{
	public:
		TutorialUi();
		~TutorialUi();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
	};
};
