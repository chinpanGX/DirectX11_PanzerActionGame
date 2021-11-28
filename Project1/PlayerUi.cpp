/*-----------------------------------------------------------

	[PlayerUi.cpp]
	Author : �o���đ�
	�v���C���[���ɕ\������UI

------------------------------------------------------------*/
#include "Engine.h"
#include "Application.h"
#include "Graphics.h"
#include "Resource.h"
#include "Reload.h"
#include "Fps.h"
#include "Pause.h"
#include "Skill.h"
#include "Status.h"
#include "Vehicle.h"
#include "Pivot.h"
#include "Player.h"
#include "GameCamera.h"
#include "PlayerUi.h"

namespace PlayerUi
{
#pragma region DrawSkill_method
	DrawSkill::DrawSkill()
	{
		m_Render = std::make_unique<Render>(*Engine::Get().graphics(), *Engine::Get().resource());
	}

	DrawSkill::~DrawSkill()
	{
	}

	void DrawSkill::Begin()
	{
		m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
		m_Pause = Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE);

		// ���������
		float t = m_Player->vehicle().skill().timeToActivateSkill();
		m_AddAmount = m_MaxDrawSize / t * Fps::Get().deltaTime;
		
		// ���炷��
		m_TimeLimit = m_Player->vehicle().skill().timeLimit();
		m_SubAmount = m_MaxDrawSize / m_TimeLimit * Fps::Get().deltaTime + 0.2f;

		m_Color = D3DXVECTOR4(0.7f, 0.7f, 0.1f, 1.0f);
		m_Time = 0.0f;
	}

	void DrawSkill::Update()
	{
		if (m_Pause->NowPausing()) { return; }
		
		// �X�L�����g�������ǂ���
		m_Use = m_Player->vehicle().skill().useSkillNow();
		// �Q�[�W�𑝂₷
		AddGage();
		Use();
	}

	void DrawSkill::Event()
	{
	}

	void DrawSkill::Draw()
	{
		// �Q�[�W�̔w�i
		D3DXVECTOR2 pos = D3DXVECTOR2(1450.0f, 940.0f);
		m_Render->Draw(m_MaxDrawSize, pos, D3DXVECTOR4(0.35f, 0.35f, 0.35f, 0.75f));

		// ���ۂ̃Q�[�W
		m_Render->Draw(m_DrawSize, pos, m_Color);
	}

#pragma region _privateFunction_
	void DrawSkill::AddGage()
	{
		// �܂��X�L�����g�����Ԃ���Ȃ�
		if (m_Player->vehicle().skill().alreadyUseble() == false)
		{
			// �Q�[�W�𑝂₷
			m_DrawSize += m_AddAmount;
			// �Q�[�W�̗ʂ̒���
			if (m_DrawSize > m_MaxDrawSize)
			{
				m_DrawSize = m_MaxDrawSize;
			}
		}
	}

	void DrawSkill::Use()
	{
		// �X�L�����g���Ă�����
		if (m_Use)
		{
			// �F�̕ύX
			m_Color = D3DXVECTOR4(0.7f, 0.1f, 1.0f, 1.0f);

			// ���Ԍv��
			m_Time += Fps::Get().deltaTime;

			// �Q�[�W�����炷
			m_DrawSize -= m_SubAmount;

			// �Q�[�W�ʂ̒���
			if (0.0f > m_DrawSize)
			{
				m_DrawSize = 0.0f;
			}
			
			// �Q�[�W���Z�b�g
			if (m_Time > m_TimeLimit)
			{
				Reset();
			}
		}
	}

	void DrawSkill::Reset()
	{
		// �`��T�C�Y��0�ɂ���
		m_DrawSize = 0.0f;
		m_Time = 0.0f;
		m_Color = D3DXVECTOR4(0.7f, 0.7f, 0.1f, 1.0f);
	}
#pragma endregion _private�֐�_
#pragma endregion �X�L���Q�[�W��`�悷��

#pragma region _Reload_
	Reload::Reload()
	{
		m_QuickReload = std::make_unique<Renderer2D>(*Engine::Get().graphics(), *Engine::Get().resource(), "Gage");
		m_ReloadIcon = std::make_unique<Renderer2D>(*Engine::Get().graphics(), *Engine::Get().resource(), "Reload");
		m_Render = std::make_unique<Render>(*Engine::Get().graphics(), *Engine::Get().resource());
		float center = static_cast<float>(SCREEN_WIDTH / 2);
		m_GagePosition = D3DXVECTOR2((center - 300.0f), 750.0f);		
		m_QuickRangePosition = D3DXVECTOR2(center, 750.0f);
		m_IconPosition = D3DXVECTOR2((center - 300.0f), 750.0f);
	}

	Reload::~Reload()
	{
	}

	void Reload::Begin()
	{
		m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
		m_Pause = Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE);

		// �����[�h���Ԃ̎擾
		float t = m_Player->vehicle().status().reloadTime();
		// ������ʂ��v�Z
		m_Amount = m_MaxSize / t * Fps::Get().deltaTime;
		
		// �ϐ��̏�����
		m_NowStop = false;
		m_Time = 0.0f;
	}

	void Reload::Update()
	{
		if (m_Pause->NowPausing()) { return; }
		
		// �����[�h��
		if (m_NowReload && m_NowStop == false)
		{
			// �����[�h���̏���
			NowReload();
			// �����[�h����
			Finish();
		}
		// �����[�h�I��
		else if(m_NowReload == false && m_NowStop == false)
		{
			// �`��̐؂�ւ�
			SwitchNotDraw();			
		}

	}

	void Reload::Event()
	{
	}

	void Reload::Draw()
	{
		// �����[�h���̂Ƃ��ɕ`��
		if (m_Draw)
		{
			auto color = D3DXVECTOR4(0.0f, 0.35f, 0.55f, 0.35f);
			// �w�i�Q�[�W
			m_Render->Draw(m_MaxSize, m_GagePosition, 15.0f, "Gage", color);

			if (m_DrawQuickGage)
			{
				color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.7f);				
				auto size = D3DXVECTOR2(160.0f, 30.0f);
				// ���������[�h�L���͈͂̃}�[�N
				m_QuickReload->Draw(m_QuickRangePosition, size);
				//m_Render->Draw(150.0f, m_QuickRangePosition, 15.0f, "Gage", color);
			}

			color = D3DXVECTOR4(1.0f, 0.5f, 0.7f, 0.5f);
			// �Q�[�W
			m_Render->Draw(m_NowGage, m_GagePosition, 15.0f, "Gage", color);

			// �A�C�R���̕`��
			DrawIcon();
		}
	}

	// �����[�h�J�n
	void Reload::BeginReload()
	{
		m_NowReload = true;
		m_Time = 0.0f;
		m_IconPosition.x = m_GagePosition.x;
		m_NowGage = 0.0f;
		// �Q�[�W�̕`��J�n
		m_Draw = true;
		m_DrawQuickGage = true;
	}

	void Reload::Stop()
	{
		m_NowStop = true;
		m_DrawQuickGage = false;
	}

	void Reload::Restart()
	{
		m_NowStop = false;
	}

	// �N�C�b�N�����[�h����
	void Reload::SuccessQuickReload()
	{
		m_EnableQuickReload = false;
		m_NowReload = false;
		m_IconPosition.x = m_GagePosition.x + m_MaxSize;
		m_NowGage = m_MaxSize;
	}

	// �����[�h���L�����ǂ���
	const bool Reload::enableQuickReload() const
	{
		return m_EnableQuickReload;
	}

#pragma region _privateFunction_
	// �����[�h�D�̏���
	void Reload::NowReload()
	{
		// �Q�[�W���ƃA�C�R���̍X�V
		m_NowGage += m_Amount;
		m_IconPosition.x += m_Amount;

		// �N�C�b�N�����[�h�͈͓̔��Ȃ�N�C�b�N�����[�h��L���ɂ���
		if (m_IconPosition.x - 40.0f > m_QuickRangePosition.x - 80.0f && m_IconPosition.x + 40.0f < m_QuickRangePosition.x + 80.0f)
		{
			m_EnableQuickReload = true;
		}
		else
		{
			m_EnableQuickReload = false;
		}
	}
	// �����[�h����
	void Reload::Finish()
	{
		if (m_Player->reload().finishReload())
		{
			m_EnableQuickReload = false;
			m_NowReload = false;
		}
	}

	// ��\���ɂ���
	void Reload::SwitchNotDraw()
	{
		// �����[�h�������������ƁA�\�����鎞�Ԃ�ݒ�
		float drawTime = 0.1f;

		// ���ԍX�V
		m_Time += Fps::Get().deltaTime;
		
		if (m_Time > drawTime)
		{
			// �Q�[�W�����ɖ߂�
			m_IconPosition.x = m_GagePosition.x;
			m_NowGage = 0.0f;

			// ��\���ɂ���
			m_Draw = false;
		}
	}

	// �A�C�R���̕`��
	void Reload::DrawIcon()
	{		
		// �N�C�b�N�����[�h���L��
		if (m_EnableQuickReload && m_DrawQuickGage)
		{
			Engine::Get().graphics()->SetBlendStateSub();
			//m_IconColor = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0);
		}
		else
		{
			m_IconColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0);
		}

		// �A�C�R��
		m_ReloadIcon->Draw(m_IconPosition, D3DXVECTOR2(80.0f, 40.0f), D3DXVECTOR2(0.0f,0.0f), D3DXVECTOR2(0.99f, 1.0f), m_IconColor);

		Engine::Get().graphics()->SetBlendStateDefault();
	}
#pragma endregion _privateFunction_
#pragma endregion _�����[�h�Q�[�W_

#pragma region _HPGage_
	Hp::Hp()
	{
		m_Render = std::make_unique<Render>(*Engine::Get().graphics(), *Engine::Get().resource());
	}

	Hp::~Hp()
	{
	}

	void Hp::Begin()
	{
		m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
		// ���ۂ�HP��MAX�̃T�C�Y����`�悷��䗦�����߂�
		m_DrawRatio = m_MaxDrawSize / m_Player->vehicle().status().maxHp();
	}

	void Hp::Update()
	{
		// ���݂�HP
		m_NowHp = m_Player->vehicle().status().hp();
		// �X�V�O��HP�Ɣ�r����
		if (m_OldHp != m_NowHp)
		{
			// ��v���Ȃ�������A�`��T�C�Y���v�Z���đO��HP���X�V����

			// ���݂�HP * ���߂��䗦
			m_DrawSize = m_NowHp * m_DrawRatio;
			m_OldHp = m_NowHp;
		}
	}

	void Hp::Event()
	{
	}

	void Hp::Draw()
	{
		// �`��ʒu��ݒ�
		D3DXVECTOR2 pos = D3DXVECTOR2(1450.0f, 900.0f);

		// MAX��Ԃ�HP�o�[
		m_Render->Draw(m_MaxDrawSize, pos, D3DXVECTOR4(0.35f, 0.35f, 0.35f, 0.75f));

		// ���݂�HP�o�[
		m_Render->Draw(m_DrawSize, pos, D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	}
#pragma endregion Hp�Q�[�W
}
