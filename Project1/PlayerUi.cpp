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

		// �Q�[�W�𑝉�����ʂ��v�Z
		float t = m_Player->vehicle().skill().timeToActivateSkill();
		m_Add = m_MaxDrawSize / t * Fps::Get().deltaTime;
	}

	void DrawSkill::Update()
	{
		if (Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE)->NowPausing()) { return; }

		// �܂��X�L�����g�����Ԃ���Ȃ�
		if (m_Player->vehicle().skill().alreadyUseble() == false)
		{
			// �Q�[�W�𑝂₷
			m_DrawSize += m_Add;
		}
	}

	void DrawSkill::Event()
	{
	}

	void DrawSkill::Draw()
	{
		D3DXVECTOR2 pos = D3DXVECTOR2(1450.0f, 940.0f);
		m_Render->Draw(m_MaxDrawSize, pos, D3DXVECTOR4(0.35f, 0.35f, 0.35f, 0.75f));
		m_Render->Draw(m_DrawSize, pos, D3DXVECTOR4(0.7f, 0.7f, 0.1f, 1.0f));
	}

	void DrawSkill::Reset()
	{
		// �`��T�C�Y���O�ɂ���
		m_DrawSize = 0.0f;
	}
#pragma endregion �X�L���Q�[�W��`�悷��

#pragma region _Reload_
	Reload::Reload()
	{
		m_Render = std::make_unique<Render>(*Engine::Get().graphics(), *Engine::Get().resource());
		m_Center = static_cast<float>(SCREEN_WIDTH / 2);
		m_GagePosition = D3DXVECTOR2((m_Center - 250.0f), 750.0f);		
		m_QuickRangePosition = D3DXVECTOR2((m_Center- 50.0f), 750.0f);
		m_IconPosition = D3DXVECTOR2((m_Center - 250.0f), 750.0f);
	}

	Reload::~Reload()
	{
	}

	void Reload::Begin()
	{
		m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
		// �����[�h���Ԃ̎擾
		float t = m_Player->vehicle().status().reloadTime();
		// ������ʂ��v�Z
		m_Amount = m_MaxSize / t * Fps::Get().deltaTime;
		m_NowStop = false;
	}

	void Reload::Update()
	{
		if (Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE)->NowPausing()) { return; }
		
		// �����[�h��
		if (m_NowReload && m_NowStop == false)
		{
				m_NowGage += m_Amount;
				m_IconPosition.x += m_Amount;
			// �N�C�b�N�����[�h�͈͓̔��Ȃ�N�C�b�N�����[�h��L���ɂ���
			if (m_IconPosition.x - 25.0f > m_QuickRangePosition.x - 50.0f && m_IconPosition.x + 25.0f < m_QuickRangePosition.x + 50.0f)
			{
				m_EnableQuickReload = true;
			}
			else
			{
				m_EnableQuickReload = false;
			}

			// �����[�h����
			if (m_Player->reload().finishReload())
			{
				m_EnableQuickReload = false;
				m_NowReload = false;
				m_IconPosition.x = m_Center - 250.0f;
			}			
		}
		// �����[�h�I��
		else if(m_NowReload == false && m_NowStop == false)
		{			
			m_NowGage = 0.0f;		
		}
	}

	void Reload::Event()
	{
	}

	void Reload::Draw()
	{
		// �����[�h���̂Ƃ��ɕ`��
		if (m_NowReload)
		{
			// �w�i�Q�[�W
			m_Render->Draw(m_MaxSize, m_GagePosition, D3DXVECTOR4(0.0f, 0.35f, 0.55f, 0.35f));

			// ���������[�h�L���͈͂̃}�[�N
			m_Render->Draw(100.0f, m_QuickRangePosition);

			// �Q�[�W
			m_Render->Draw(m_NowGage, m_GagePosition, D3DXVECTOR4(1.0f, 0.5f, 0.7f, 0.5f));

			// �L�����ǂ����ŐF��ς���
			if (m_EnableQuickReload)
			{
				m_IconColor = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0);
			}
			else
			{
				m_IconColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0);
			}
			
			// �A�C�R�� 
			m_Render->Draw(50.0f, m_IconPosition, m_IconColor);
		}
	}
	// �����[�h�J�n
	void Reload::BeginReload()
	{
		m_NowReload = true;
	}

	void Reload::OnStop()
	{
		m_NowStop = true;
	}

	void Reload::OffStop()
	{
		m_NowStop = false;
	}

	// �����[�h���L�����ǂ���
	const bool Reload::enableQuickReload() const
	{
		return m_EnableQuickReload;
	}
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
