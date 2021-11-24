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
		
		void BeginReload();
		void OnStop(); // �����[�h���~�߂�
		void OffStop();

		// �N�C�b�N�����[�h����
		void SuccessQuickReload();
		void FailedQuickReload();

		// �N�C�b�N�����[�h���L�����ǂ����Ԃ�
		const bool enableQuickReload()const;		
	private:
		// �����[�h�I��
		void Finish();

		D3DXVECTOR4 m_IconColor; // �A�C�R���̐F
		
		D3DXVECTOR2 m_GagePosition; // �Q�[�W�̈ʒu
		D3DXVECTOR2 m_QuickRangePosition;	// �N�C�b�N�����[�h�͈�
		D3DXVECTOR2 m_IconPosition;

		std::unique_ptr<Render> m_Render;
		Player* m_Player;

		// �Q�[�W�̃T�C�Y
		const float m_MaxSize = 500.0f; // MAX�T�C�Y
		float m_Center; // ��ʒ���
		float m_NowGage = 0.0f;			// 		
		float m_Amount; // �������
		
		float m_Time;

		bool m_NowStop; // �X�g�b�v�����ǂ���
		bool m_NowReload = false; // �����[�h�����ǂ���
		bool m_EnableQuickReload = false;
		bool m_Draw = false; // �`�悷�邩�ǂ���
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