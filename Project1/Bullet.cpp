/*-----------------------------------------------------------

	[Bullet.cpp]
	Author : �o���đ�

	�e�̏���

-------------------------------------------------------------*/
#include "Vehicle.h"
#include "Engine.h"
#include "Resource.h"
#include "BulletStateMove.h"
#include "BulletStateDestory.h"
#include "Fps.h"
#include "Engine.h"
#include "Application.h"
#include "MuzzleFlash.h"
#include "Player.h" 
#include "Enemy.h"
#include "Fence.h"
#include "WallBox.h"
#include "Bullet.h"

Bullet::Bullet() : m_Resource(*Engine::Get().GetResource()), m_FrameZeroFlag(false)
{
}

Bullet::~Bullet()
{
	m_FrameZeroFlag = false;
}

inline void Bullet::Begin()
{
}

inline void Bullet::Update()
{
	m_State->Update(this, Fps::Get().deltaTime);
	UpdateCollision(*m_Collider);

	// �t���[��0�ɂȂ�����폜
	m_Frame--;
	if (m_Frame < 0)
	{
		Destroy();
	}
}

inline void Bullet::Event()
{
	// ����������A����
	if (CollisionEnter())
	{
		ChangeState(std::make_unique<BulletStateDestory>());
	}
}

inline void Bullet::Draw()
{
	m_Resource.SetShader("Default");
	// �}�g���N�X�ݒ�
	Actor::UpdateMatrix(*m_Transform);
	m_Resource.SetStaticModel("Bullet");
}

void Bullet::Create(const D3DXVECTOR3 & Position, const D3DXVECTOR3 & Vector)
{
	// �ϐ��̏�����
	m_DirectionVector = Vector;
	m_Speed = 300.0f;
	m_Frame = 240;
	
	// �C���X�^���X����
	m_Transform = AddComponent<Transform>();
	m_Transform->SetPosition(Position);
	m_Transform->SetScale(1.5f);

	// �R���|�[�l���g�̐ݒ�
	m_Collider = AddComponent<Collider>();
	D3DXVECTOR3 scale = m_Transform->GetScale() * 0.5f;
	m_Collider->SetSphere3(*m_Transform, 1.0f);
	m_Collider->SetAABB3(*m_Transform, scale);
	m_Collider->SetOBB3(*m_Transform, scale);
	m_State = std::make_unique<BulletStateMove>();

	// ���\�[�X
	auto effect = Engine::Get().GetApplication()->GetScene()->AddGameObject<Billboard::MuzzleFlash>(ELayer::LAYER_2D_EFFECT);
	effect->GetTransform().SetPosition(Position);
}

void Bullet::ChangeState(std::unique_ptr<BulletState> State)
{
	m_State = std::move(State);
}

void Bullet::OnCollision()
{
	// �v���C���[
	auto player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (player)
	{
		OnCollisionToPawn(player);
	}

	// �G�l�~�[
	auto enemy_1 = Engine::Get().GetApplication()->GetScene()->GetGameObject<Enemy>(ELayer::LAYER_3D_ACTOR);
	if (enemy_1)
	{
		OnCollisionToPawn(enemy_1);
	}

	// �t�F���X
	std::vector<Fence*> fences = Engine::Get().GetApplication()->GetScene()->GetGameObjects<Fence>(ELayer::LAYER_3D_STAGE);
	for (Fence* fence : fences)
	{
		if (Intersect(m_Collider->GetAABB3(), fence->GetCollider().GetAABB3()))
		{
			Bullet::OnCollisionEnter();
			fence->OnCollisionEnter();
		}
	}

	// ��
	auto walls = Engine::Get().GetApplication()->GetScene()->GetGameObjects<WallBox>(ELayer::LAYER_3D_STAGE);
	for (auto i : walls)
	{
		if (Intersect(m_Collider->GetAABB3(), i->GetCollider().GetAABB3()))
		{
			Bullet::OnCollisionEnter();
			i->OnCollisionEnter();
		}
	}
}

const D3DXVECTOR3 & Bullet::GetDirectionVector() const
{
	return m_DirectionVector;
}

void Bullet::DownDDE()
{
	m_Distdecay -= 0.02f; // ������

	// �Œ�l��ݒ肷��
	if (m_Distdecay < 0.7f)
	{
		m_Distdecay = 0.7f;
	}
}

const float Bullet::GetDistdecay() const
{
	return m_Distdecay;
}

const float Bullet::GetSpeed() const
{
	return m_Speed;
}

void Bullet::OnCollisionToPawn(Pawn * Pawn)
{
	// �����m�̓����蔻������
	if (Intersect(m_Collider->GetSphere3(), Pawn->GetVehicle().GetCollider(0).GetSphere3()))
	{
		// ��Ԃ����R���C�_�[�̕����[�v
		for (uint32_t i = 0; i < Pawn->GetVehicle().GetColliderNum(); i++)
		{
			if (Intersect(m_Collider->GetOBB3(), Pawn->GetVehicle().GetCollider(i).GetOBB3()))
			{
				Bullet::OnCollisionEnter();
				Pawn->OnCollisionEnter();
				// ���������烋�[�v�𔲂���
				break;
			}
		}
	}
}
