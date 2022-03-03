/*------------------------------------------------------------

	[GameBg.h]
	Author : 出合翔太

	ゲームの2D背景

-------------------------------------------------------------*/
#pragma once
#include "Bg.h"
#include <array>
#include <vector>

class GameCamera;
class SelectCommand;
class PanzerContainer;
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
	private:
		GameCamera* m_Camera;
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
		void DrawGameRule(D3DXVECTOR2 Position, D3DXVECTOR2 Size);	// ゲーム説明	

		std::vector<D3DXVECTOR2> m_TexCoord;
		std::array<std::unique_ptr<Renderer2D>, 3> m_Render;
		PanzerContainer* m_Container;
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
		void DrawFrame(D3DXVECTOR2 Position, float Size_y);	// 背景枠の点滅
		void DrawModeName(D3DXVECTOR2 Position, float Size_y);	// ゲームモード

		std::unique_ptr<Renderer2D> m_BgFrame;
		SelectCommand* m_Command; 
		bool m_TutorialMode; // trueでチュートリアル、falseでゲーム
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
