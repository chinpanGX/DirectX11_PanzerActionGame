/*--------------------------------------------------------------

	[Enemy.cpp]
	Author : �o���đ�

---------------------------------------------------------------*/
#include "PanzerState.h"
#include "PanzerContainer.h"
#include "Engine.h"
#include "Application.h"
#include "Resource.h"
#include "Pivot.h"
#include "Fps.h"
#include "Body.h"
#include "Turret.h"
#include "MainGun.h"
#include "PanzerStateStay.h"
#include "Factory.h"
#include "Pause.h"
#include "Reload.h"
#include "Player.h"
#include "Skill.h"
#include "Vehicle.h"
#include "Command.h"
#include "MoveComponent.h"
#include "GameCamera.h"
#include "Supply.h"
#include "Bullet.h"
#include "Enemy.h"

Enemy::Enemy() : Pawn(Factory::FVehicle::EType::E_CPU), m_Resource(*Engine::Get().GetResource()), m_Graphics(*Engine::Get().GetGraphics())
{
	Pawn::Create();	
}

Enemy::~Enemy()
{
}

void Enemy::Begin()
{
	m_SupplyList = Engine::Get().GetApplication()->GetScene()->GetGameObjects<Supply>(ELayer::LAYER_3D_STAGE);
	m_Pause = Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE);
	m_Player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	m_Camera = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	m_CpuReload = std::make_unique<CpuReload>();
	m_CpuReload->Begin();
	float rand_x = (float)myLib::Random::Rand_R(-100, 100);
	Pawn::SetStartPosition(this, D3DXVECTOR3(rand_x, 0.0f, 180.0f), D3DXVECTOR3(0.0f, Math::ToRadians(180.0f), 0.0f));
	m_State = std::make_unique<State::Stay>();
	m_State->Begin(m_Player);
}

void Enemy::Update()
{
	if(m_Pause->NowPausing()) { return; }	
	m_State->Update(this, Fps::Get().deltaTime);
	m_CpuReload->Update();
	Pawn::Update();
	OnCollision();
}

void Enemy::Event()
{
	if (CollisionEnter())
	{
		float attackpt = 0.0f; // �^����_���[�W
		auto bulletList = Engine::Get().GetApplication()->GetScene()->GetGameObjects<Bullet>(ELayer::LAYER_3D_ACTOR);
		for (auto bullet : bulletList)
		{
			// ��������(50 �` 100)�̕␳������
			int rand = myLib::Random::Rand_R(50, 100);
			attackpt = m_Player->GetVehicle().GetStatus().GetAttack() + rand * bullet->GetDistdecay() - GetVehicle().GetStatus().GetDefence();
			// MAX��Ԃ�HP���擾����
			float maxHp = GetVehicle().GetStatus().GetMaxHp();
			// ���݂�HP���猸�Z
			float nowHp = GetVehicle().GetStatus().GetHp() - attackpt;
			GetVehicle().GetStatus().SetHp(nowHp);
		}
		ResetCollisionEnter();
	}
	Pawn::CheckZeroHp(this);
}

void Enemy::Draw()
{
	m_IsNotDraw = m_Camera->NotDrawObject(GetPivot().GetTransform().GetPosition(), GetVehicle().GetCollider(0).GetSphere3().GetRadius());
	if (m_IsNotDraw) { return; }

	// �V�F�[�_�[�̐ݒ�
	m_Resource.SetVertexShader("PixelLighting");
	m_Resource.SetInputLayout("PixelLighting");
	// �X�L�����g���Ă��邩
	if (GetVehicle().GetSkill().GetUseSkillNow())
	{
		// �X�L�����g���Ă���Ƃ��̐ݒ�
		m_Resource.SetPixelShader("ToonAnim");
		m_Resource.SetTexture(1, "ToonAnim");
		D3DXVECTOR4 uv = GetVehicle().GetSkill().GetTexUV();
		m_Graphics.SetParameter(uv);
	}
	else
	{
		// �f�t�H���g�̐ݒ�
		m_Resource.SetPixelShader("PixelLighting");
		//m_Resource.SetPixelShader("Toon");
		//m_Resource.SetTexture(1, "Toon");
	}
	GetVehicle().Draw();
}

void Enemy::ChangeState(std::unique_ptr<PanzerState> State)
{
	m_State = std::move(State);
	m_State->Begin(m_Player);
}

void Enemy::ResPawn(const D3DXVECTOR3 & pos)
{
	GetVehicle().GetSkill().Reset(GetVehicle().GetStatus());
	GetVehicle().GetStatus().Reset();
	// �X�L���̏�Ԃ����Z�b�g
	SetStartPosition(this, pos, D3DXVECTOR3(0.0f, Math::ToRadians(180.0f), 0.0f));
	this->ChangeState(std::make_unique<State::Stay>());
}

void Enemy::UseSkill()
{
	GetVehicle().GetSkill().Enable(this);
	GetVehicle().GetSkill().PlayEffect(this);
}

bool Enemy::IsDraw() const
{
	// �`�悵�Ă��Ȃ��Ȃ�false��Ԃ�
	if (m_IsNotDraw == true)
	{
		return false;
	}
	// �`�悵�Ă���
	return true;
}

CpuReload & Enemy::GetReload() const
{
	return *m_CpuReload;
}

void Enemy::OnCollision()
{
	BeginOverlap(this);
}
