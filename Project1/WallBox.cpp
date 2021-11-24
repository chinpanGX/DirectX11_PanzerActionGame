/*--------------------------------------------------------------

	[WallFence.cpp]
	Author : �o���đ�

	�g���[�j���O�p�̕�

---------------------------------------------------------------*/
#include "Resource.h"
#include "Engine.h"
#include "Application.h"
#include "GameCamera.h"
#include "WallBox.h"
#include "Collision.h"

WallBox::WallBox()
{
	m_Transform = Actor::AddComponent<Transform>();
	m_Collider = Actor::AddComponent<Collider>();
}

WallBox::~WallBox()
{
}

void WallBox::Begin()
{
	m_Camera = Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
}

void WallBox::Update()
{
	Actor::UpdateCollision(*m_Collider);
}

void WallBox::Event()
{
}

void WallBox::Draw()
{
	if (m_Camera->NotDrawObject(m_Transform->position(), StageObject::radius()))
	{
		return;
	}

	resource().SetShader("Default");
	UpdateMatrix(*m_Transform);
	resource().SetStaticModel("WallFence");
}

void WallBox::Set(const D3DXVECTOR3 & Pos, const D3DXVECTOR3 & Size, int Normal)
{
	m_Transform->Set(Pos, Size);
	m_Collider->SetOBB3(*m_Transform, m_Transform->scale());
	m_Collider->SetAABB3(*m_Transform, m_Transform->scale());
	
	// �`�攼�a
	StageObject::radius(D3DXVec3Length(&Size));

	// �߂荞�ݖh�~�̕��ʂ����
	CreatePlane(Normal);
}

D3DXVECTOR3 WallBox::OffsetLength(const OBB3 & obj)
{
	// �߂荞�񂾋���
 	float length = 0.0f;

	float r = 0.0f; //�@�ߐڋ���
	OBB3 target = obj;
	auto pos = target.position();

	// x
	D3DXVECTOR3 direct = target.GetDirection(0);
	float len = target.GetLength().x;
	r += fabs(D3DXVec3Dot(&D3DXVECTOR3(direct * len), &m_Normal));

	// y
	direct = target.GetDirection(1);
	len = target.GetLength().y;
	r += fabs(D3DXVec3Dot(&D3DXVECTOR3(direct * len), &m_Normal));

	// z
	direct = target.GetDirection(2);
	len = target.GetLength().z;
	r += fabs(D3DXVec3Dot(&D3DXVECTOR3(direct * len), &m_Normal));

	auto tmp = pos - m_PlanePoint;
	D3DXVec3Normalize(&m_Normal, &m_Normal);
	float s = D3DXVec3Dot(&tmp, &m_Normal);

	// �Փ˂��Ă���
	if (fabs(s) - r < 0.0f)
	{
		if (s > 0)
		{
			length = r - fabs(s);
		}
		else
		{
			length = r + fabs(s);
		}
	}
	
	// �@���x�N�g�� * �߂荞�񂾋��� = ���˕Ԃ��x�N�g��
	return m_Normal * length;
}

void WallBox::CreatePlane(int Normal)
{
	D3DXVECTOR3 pos = m_Transform->position();
	D3DXVECTOR3 size = m_Transform->scale();

	// �@���̌����ƕ��ʂ̈ʒu�����߂�
	switch (Normal)
	{
	case 0:
		m_Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		break;
	case g_UnitX:
		m_Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		m_PlanePoint = D3DXVECTOR3(pos.x + size.x, pos.y, pos.z);
		break;
	case g_NegUnitX:
		m_Normal = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		m_PlanePoint = D3DXVECTOR3(pos.x - size.x, pos.y, pos.z);
		break;
	case g_UnitZ:
		m_Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		m_PlanePoint = D3DXVECTOR3(pos.x, pos.y, pos.z + size.z);
		break;
	case g_NegUnitZ:
		m_Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		m_PlanePoint = D3DXVECTOR3(pos.x, pos.y, pos.z - size.z);
		break;		
	}
}