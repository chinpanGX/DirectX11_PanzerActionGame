/*-----------------------------------------------------------

	[PlayerUi.cpp]
	Author : �o���đ�
	�v���C���[���ɕ\������UI

------------------------------------------------------------*/
#include "Engine.h"
#include "Application.h"
#include "Graphics.h"
#include "Resource.h"
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
		if (Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->NowPausing()) { return; }

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

	Reload::Reload() : Effect()
	{
		m_Transform = Actor::AddComponent<Transform>();
	}

	Reload::~Reload()
	{
	}

	void Reload::Begin()
	{
		m_Transform->Begin();
	}

	void Reload::Update()
	{
		if (Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->NowPausing()) { return; }

		auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
		m_Transform->rotation().z += 0.05f;
		// �v���C���[�̃����[�h����������΍폜
		if (player->vehicle().status().finishReload() == true)
		{
			OnDestroy();
		}
	}

	void Reload::Event()
	{
	}

	void Reload::Draw()
	{
		// �}�g���N�X�̐ݒ�
		// �J�����̏����擾
		auto camera = Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
		D3DXMATRIX view = camera->view();

		// �r���[�̋t�s��
		D3DXMATRIX invView;
		D3DXMatrixInverse(&invView, nullptr, &view);//�t�s��
		invView._41 = 0.0f;
		invView._42 = 0.0f;
		invView._43 = 0.0f;

		// ��Ԃ̏����擾
		auto& pivot = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->pivot();
		// ��Ԃ̈ʒu�ɃG�t�F�N�g�̈ʒu�����킹��
		m_Transform->position().x = pivot.transform().position().x;
		m_Transform->position().z = pivot.transform().position().z;

		// ���W�ϊ�
		D3DXMATRIX scale, rot, trans;
		Math::Matrix::MatrixScaling(&scale, m_Transform->scale());
		Math::Matrix::MatrixRotationRollPitchYaw(&rot, m_Transform->rotation());
		Math::Matrix::MatrixTranslation(&trans, m_Transform->position());
		D3DXMATRIX world = scale * rot * invView * trans;
		m_Graphics.SetWorldMatrix(world);

		// �}�e���A��
		Material m;
		m.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Graphics.SetMaterial(m);

		// �e�N�X�`���̐ݒ�
		m_Resource.SetTexture(0, "Reload");

		Effect::Draw();
	}
#pragma region _ReloadGage_
	ReloadGage::ReloadGage()
	{
		m_Render = std::make_unique<Render>(*Engine::Get().graphics(), *Engine::Get().resource());
		m_Position = D3DXVECTOR2(static_cast<float>((SCREEN_WIDTH / 2) - 250.0f), 940.0f);
	}
	ReloadGage::~ReloadGage()
	{
	}
	void ReloadGage::Begin()
	{

	}
	void ReloadGage::Update()
	{
	}
	void ReloadGage::Event()
	{
	}
	void ReloadGage::Draw()
	{
		m_Render->Draw(m_MaxSize, m_Position, D3DXVECTOR4(0.35f, 0.35f, 0.35f, 0.75f));
		//m_Render->Draw(m_NowGage, pos, D3DXVECTOR4(0.7f, 0.7f, 0.1f, 1.0f));
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
