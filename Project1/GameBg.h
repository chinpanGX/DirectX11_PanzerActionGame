/*------------------------------------------------------------

	[GameBg.h]
	Author : oγΔΎ

	Q[Μ2Dwi

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
	// XR[v
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

	// IπζΚwiUI
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
		// `ζ
		void DrawPanzerName();	// νΤΜΌO
		void DrawGameRule(D3DXVECTOR2 Position, D3DXVECTOR2 Size);	// Q[ΰΎ	

		std::vector<D3DXVECTOR2> m_TexCoord;
		std::array<std::unique_ptr<Renderer2D>, 3> m_Render;
		PanzerContainer* m_Container;
		int32_t m_Page;
		bool m_DrawFlag = false;
	};

	// [hIπ
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
		// `ζ
		void DrawFrame(D3DXVECTOR2 Position, float Size_y);	// wigΜ_Ε
		void DrawModeName(D3DXVECTOR2 Position, float Size_y);	// Q[[h

		std::unique_ptr<Renderer2D> m_BgFrame;
		SelectCommand* m_Command; 
		bool m_TutorialMode; // trueΕ`[gAAfalseΕQ[
		float m_Alpha = 1.0f;
		float m_Color = 0.01f;
	};

	// `[gAΜμΰΎ
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
