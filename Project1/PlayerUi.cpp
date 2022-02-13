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
		m_Render = std::make_unique<Render>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource());
	}

	DrawSkill::~DrawSkill()
	{
	}

	void DrawSkill::Begin()
	{
		m_Player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
		m_Pause = Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE);

		// ���������
		float t = m_Player->GetVehicle().GetSkill().timeToActivateSkill();
		m_AddAmount = m_MaxDrawSize / t * Fps::Get().deltaTime;
		
		// ���炷��
		m_TimeLimit = m_Player->GetVehicle().GetSkill().timeLimit();
		m_SubAmount = m_MaxDrawSize / m_TimeLimit * Fps::Get().deltaTime + 0.2f;

		m_Color = D3DXVECTOR4(0.7f, 0.7f, 0.1f, 1.0f);
		m_Time = 0.0f;
	}

	void DrawSkill::Update()
	{
		if (m_Pause->NowPausing()) { return; }
		
		// �X�L�����g�������ǂ���
		m_Use = m_Player->GetVehicle().GetSkill().useSkillNow();
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

	void DrawSkill::Reset()
	{
		// �`��T�C�Y��0�ɂ���
		m_DrawSize = 0.0f;
		m_Time = 0.0f;
		m_Color = D3DXVECTOR4(0.7f, 0.7f, 0.1f, 1.0f);
	}

#pragma region _privateFunction_
	void DrawSkill::AddGage()
	{
		// �܂��X�L�����g�����Ԃ���Ȃ�
		if (m_Player->GetVehicle().GetSkill().alreadyUseble() == false)
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
#pragma endregion _private�֐�_
#pragma endregion �X�L���Q�[�W��`�悷��

#pragma region _Reload_
	Reload::Reload()
	{
		m_QuickReload = std::make_unique<Renderer2D>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource(), "Gage");
		m_ReloadIcon = std::make_unique<Renderer2D>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource(), "Reload");
		m_Render = std::make_unique<Render>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource());
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
		m_Player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
		m_Pause = Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE);

		// �����[�h���Ԃ̎擾
		float t = m_Player->GetVehicle().GetStatus().reloadTime();
		// ������ʂ��v�Z
		m_DefaultAmount = m_MaxSizeAmount / t * Fps::Get().deltaTime;

		m_QuickAmount = m_MaxSizeAmount / 0.5f * Fps::Get().deltaTime;
		
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
			m_Render->Draw(m_MaxSizeAmount, m_GagePosition, 15.0f, "Gage", color);

			if (m_DrawQuickGage)
			{
				color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.7f);				
				auto size = D3DXVECTOR2(160.0f, 30.0f);
				// ���������[�h�L���͈͂̃}�[�N
				m_QuickReload->Draw(m_QuickRangePosition, size);
			}

			color = D3DXVECTOR4(1.0f, 0.5f, 0.7f, 0.5f);
			// �Q�[�W
			m_Render->Draw(m_NowGageAmount, m_GagePosition, 15.0f, "Gage", color);

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
		m_NowGageAmount = 0.0f;
		// �Q�[�W�̕`��J�n
		m_Draw = true;
		m_DrawQuickGage = true;
		m_MatchCount = true;
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
		m_IconPosition.x = m_GagePosition.x + m_MaxSizeAmount;
		m_NowGageAmount = m_MaxSizeAmount;
	}

	// �����[�h���L�����ǂ���
	const bool Reload::enableQuickReload() const
	{
		return m_EnableQuickReload;
	}

	void Reload::enableQuickReload(bool Flag)
	{
		m_MatchCount = Flag;
	}

#pragma region _privateFunction_
	// �����[�h�̏���
	void Reload::NowReload()
	{		
		// �N�C�b�N�����[�h�͈͓̔��Ȃ�N�C�b�N�����[�h��L���ɂ���
		if (m_IconPosition.x - 40.0f > m_QuickRangePosition.x - 80.0f && m_IconPosition.x + 40.0f < m_QuickRangePosition.x + 80.0f)
		{
			m_EnableQuickReload = true;
		}
		else
		{
			m_EnableQuickReload = false;
		}

		// �Q�[�W���ƃA�C�R���̍X�V		
		// �X�L�����g�p��
		if (m_Player->GetVehicle().GetSkill().useSkillNow())
		{
			AddGageAndMoveIcon(m_QuickAmount);
		}
		// �X�L�����g���Ă��Ȃ�
		else
		{
			AddGageAndMoveIcon(m_DefaultAmount);
		}
		
	}

	void Reload::AddGageAndMoveIcon(float amount)
	{
		m_NowGageAmount += amount;
		m_IconPosition.x += amount;
	}

	// �����[�h����
	void Reload::Finish()
	{
		if (m_Player->GetReload().finishReload())
		{
			m_NowGageAmount = m_MaxSizeAmount;
			m_IconPosition.x = m_GagePosition.x + m_MaxSizeAmount;
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
			
			m_NowGageAmount = 0.0f;

			// ��\���ɂ���
			m_Draw = false;
		}
	}

	// �A�C�R���̕`��
	void Reload::DrawIcon()
	{	
		auto size = D3DXVECTOR2(80.0f, 38.0f);
		auto min = D3DXVECTOR2(0.0f, 0.0f);
		auto max = D3DXVECTOR2(0.99f, 1.0f);
		D3DXVECTOR4 color;

		// �f�t�H���g�̐ݒ�
		Engine::Get().GetResource()->SetVertexShader("NoLighting");
		Engine::Get().GetResource()->SetInputLayout("NoLighting");
	
		// �N�C�b�N�����[�h���L�� �܂��̓����[�h���Ă��Ȃ��Ƃ�
		if (m_EnableQuickReload && m_MatchCount || m_NowReload == false)
		{			
			Engine::Get().GetResource()->SetPixelShader("NoLighting");
			color = D3DXVECTOR4(0.85f, 0.95f, 0.0f, 1.0);
		}	
		else
		{
			Engine::Get().GetResource()->SetPixelShader("GrayScaleTexture");
			color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0);
		}
		// �A�C�R��
		m_ReloadIcon->Draw(m_IconPosition, size, min, max, color, false);
	}
#pragma endregion _privateFunction_
#pragma endregion _�����[�h�Q�[�W_

#pragma region _HPGage_
	Hp::Hp()
	{
		m_Render = std::make_unique<Render>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource());
	}

	Hp::~Hp()
	{
	}

	void Hp::Begin()
	{
		m_Player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
		// ���ۂ�HP��MAX�̃T�C�Y����`�悷��䗦�����߂�
		m_DrawRatioAmount = m_MaxDrawSize / m_Player->GetVehicle().GetStatus().maxHp();
	}

	void Hp::Update()
	{
		// ���݂�HP
		m_NowHpAmount = m_Player->GetVehicle().GetStatus().hp();
		// �X�V�O��HP�Ɣ�r����
		if (m_OldHpAmount != m_NowHpAmount)
		{
			// ��v���Ȃ�������A�`��T�C�Y���v�Z���đO��HP���X�V����

			// ���݂�HP * ���߂��䗦
			m_DrawSizeAmount = m_NowHpAmount * m_DrawRatioAmount;
			m_OldHpAmount = m_NowHpAmount;
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
		m_Render->Draw(m_DrawSizeAmount, pos, D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	}
#pragma endregion Hp�Q�[�W
}
