/*-----------------------------------------------------------

	[PlayerUi.h]
	Author : �o���đ�
	�v���C���[���ɕ\������UI

------------------------------------------------------------*/
#pragma once
#include "Actor.h"
#include "Effect.h"

class Render;
class Player;
namespace PlayerUi
{	
	// �X�L���̃Q�[�W
	class DrawSkill final : public Actor
	{
	public:
		DrawSkill();
		~DrawSkill();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
		void Reset();
	private:
		std::unique_ptr<Render> m_Render;
		Player* m_Player;
		const float m_MaxDrawSize = 400.0f;
		float m_DrawSize = 0.0f;
		float m_Add; // ���������
	};

	// �����[�h�Q�[�W
	class Reload final : public Actor
	{
	public:
		Reload();
		~Reload();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
		
		void OnReload();
	private:
		D3DXVECTOR2 m_Position;
		std::unique_ptr<Render> m_Render;
		Player* m_Player;
		const float m_MaxSize = 500.0f;
		float m_NowGage = 0.0f;
		float m_Amount;
		bool m_NowReload = false; // �����[�h��
	};

	// Hp�Q�[�W
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
		std::unique_ptr<Render> m_Render;
		Player* m_Player;
		const float m_MaxDrawSize = 400.0f; // MAX���HP

		// �v���C���[��HP
		float m_NowHp = 0.0f; // ���݂�HP
		float m_OldHp = 0.0f; // �X�V�O��HP

		// �`��
		float m_DrawSize = 400.0f; // ����HP
		float m_DrawRatio = 0.0f; // �`�� �䗦		
	};
}