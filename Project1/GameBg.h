/*------------------------------------------------------------

	[GameBg.h]
	Author : �o���đ�

	�Q�[����2D�w�i

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
	// �X�R�[�v
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

	// �I����ʔw�iUI
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
		// �`��
		void DrawPanzerName();	// ��Ԃ̖��O
		void DrawGameRule(D3DXVECTOR2 Position, D3DXVECTOR2 Size);	// �Q�[������	

		std::vector<D3DXVECTOR2> m_TexCoord;
		std::array<std::unique_ptr<Renderer2D>, 3> m_Render;
		PanzerContainer* m_Container;
		int32_t m_Page;
		bool m_DrawFlag = false;
	};

	// ���[�h�I��
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
		// �`��
		void DrawFrame(D3DXVECTOR2 Position, float Size_y);	// �w�i�g�̓_��
		void DrawModeName(D3DXVECTOR2 Position, float Size_y);	// �Q�[�����[�h

		std::unique_ptr<Renderer2D> m_BgFrame;
		SelectCommand* m_Command; 
		bool m_TutorialMode; // true�Ń`���[�g���A���Afalse�ŃQ�[��
		float m_Alpha = 1.0f;
		float m_Color = 0.01f;
	};

	// �`���[�g���A���̑������
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
