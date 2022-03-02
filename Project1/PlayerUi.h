/*-----------------------------------------------------------

	[PlayerUi.h]
	Author : �o���đ�
	�v���C���[���ɕ\������UI

------------------------------------------------------------*/
#pragma once
#include "Actor.h"
#include "Effect.h"

class Pause;
class RenderGage;
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
		/* �X�V�����̃w���p�[�֐� */
		void AddGage();
		void Use();

		D3DXVECTOR4 m_Color;
		std::unique_ptr<RenderGage> m_Render;
		Player* m_Player;
		Pause* m_Pause;

		const float m_MaxDrawSize = 400.0f;
		float m_DrawSize = 0.0f;
		float m_TimeLimit;
		float m_Time;
		float m_AddAmount; // ���������
		float m_SubAmount; // ���炵�Ă�����

		bool m_Use;
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
		
		void BeginReload();			// �����[�h�J�n
		void Stop();				// �����[�h���~�߂�
		void Restart();				// ���X�^�[�g
		void SuccessQuickReload();	// �N�C�b�N�����[�h����

		// �N�C�b�N�����[�h���L�����ǂ����Ԃ�
		const bool GetEnableQuickReload()const;		
		void SetEnableQuickReload(bool Flag);
	private:
		/* �X�V�����̃w���p�[�֐� */
		void NowReload();			// �����[�h�̏���
		void AddGageAndMoveIcon(float Amount);	// �Q�[�W�𑝂₷�����ƃA�C�R���𑝂₷
		void Finish();				// �����[�h�I��
		void SwitchNotDraw();		// ��\���ɂ���

		/* �`�揈���̃w���p�[�֐� */
		void DrawIcon();

		D3DXVECTOR2 m_GagePosition;			// �Q�[�W�̈ʒu
		D3DXVECTOR2 m_QuickRangePosition;	// �N�C�b�N�����[�h�͈�
		D3DXVECTOR2 m_IconPosition;			// �A�C�R���̈ʒu

		std::unique_ptr<Renderer2D> m_ReloadIcon;
		std::unique_ptr<Renderer2D> m_QuickReload;
		std::unique_ptr<RenderGage> m_Render;
		Player* m_Player;
		Pause* m_Pause;

		// �Q�[�W�̃T�C�Y
		const float m_MaxSizeAmount = 600.0f; // MAX�T�C�Y
		float m_NowGageAmount = 0.0f;			// 		
		float m_DefaultAmount;	// �f�t�H���g�̑������
		float m_QuickAmount;	// �N�C�b�N�̑������	

		float m_Time;

		bool m_DrawQuickGage = true; // ���������[�h�̕\��
		bool m_NowStop = false; // �X�g�b�v�����ǂ���
		bool m_NowReload = false; // �����[�h�����ǂ���
		bool m_EnableQuickReload = false;
		bool m_MatchCount;
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
		std::unique_ptr<RenderGage> m_Render;
		Player* m_Player;
		const float m_MaxDrawSize = 400.0f; // MAX���HP

		// �v���C���[��HP
		float m_NowHpAmount = 0.0f; // ���݂�HP
		float m_OldHpAmount = 0.0f; // �X�V�O��HP

		// �`��
		float m_DrawSizeAmount = 400.0f; // ����HP
		float m_DrawRatioAmount = 0.0f; // �`�� �䗦		
	};
}