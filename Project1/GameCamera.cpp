/*-------------------------------------------------------------
	
	[GameCamera.cpp]
	Author : �o���đ�

--------------------------------------------------------------*/
#include "Engine.h"
#include "Graphics.h"
#include "Application.h"
#include "GameCamera.h"
#include "Player.h"
#include "Pivot.h"

#pragma region CameCamera_method
GameCamera::GameCamera() : m_Position(D3DXVECTOR3(0.0f, 5.0f, -8.0f)), m_Target(D3DXVECTOR3(0.0f, 0.0f, 0.0f)), m_Graphics(*Engine::Get().graphics()), m_EnableFpsMode(false)
{
	
}

GameCamera::~GameCamera()
{

}

void GameCamera::Begin()
{
	m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
}

void GameCamera::Update()
{
	const auto& pivot = m_Player->pivot();

	// FPS���[�h
	if (m_EnableFpsMode)
	{
		m_Position = pivot.transform().position() + (pivot.transform().forward() * pivot.GetFpsOffset());
		m_Target = pivot.transform().position() + (pivot.transform().forward() * pivot.GetTargetOffset());
	}
	// TPS���[�h	
	else
	{
		auto offset = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
		m_Position = pivot.transform().position() + (-pivot.transform().forward() * pivot.GetTpsOffset()) + offset;
		m_Target = pivot.transform().position() + (pivot.transform().forward() * pivot.GetTargetOffset());
	}

}

void GameCamera::Event()
{
}

void GameCamera::Draw()
{
	// �r���[�}�g���N�X�̐ݒ�
	SetViewMatrix();

	// �v���W�F�N�V�����}�g���N�X�̐ݒ�
	SetProjectionMatrix();
}

bool GameCamera::NotDrawObject(const D3DXVECTOR3& TargetPosition, float Radius)
{
	D3DXMATRIX vp, invvp;

	vp = m_View * m_Projection;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	// far�ʂ̍��W
	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vpos[1] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	// ���W�ϊ�
	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);

	D3DXVECTOR3 v, v1, v2, n;
	float dot;

	// ����
	// �J�����ƑΏۂ̃I�u�W�F�N�g�̃x�N�g��
	v = TargetPosition - m_Position;

	// �@���x�N�g�������߂� 
	v1 = wpos[0] - m_Position;
	v2 = wpos[2] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);
	D3DXVec3Normalize(&n, &n);
	dot = D3DXVec3Dot(&n, &v);
	if (dot < -Radius)
	{
		//OutputDebugString("�����ŏ����Ă���\n");
		return true;
	}

	// �E��
	v1 = wpos[1] - m_Position;
	v2 = wpos[3] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);
	D3DXVec3Normalize(&n, &n);
	dot = D3DXVec3Dot(&n, &v);
	if (dot > Radius)
	{
		// OutputDebugString("�E���ŏ����Ă���\n");
		return true;
	}

	// �㑤
	v1 = wpos[0] - m_Position;
	v2 = wpos[1] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);
	D3DXVec3Normalize(&n, &n);
	dot = D3DXVec3Dot(&n, &v);
	if (dot > Radius)
	{
		//OutputDebugString("�㑤�ŏ�����\n");
		return true;
	}

	// ����
	v1 = wpos[2] - m_Position;
	v2 = wpos[3] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);
	D3DXVec3Normalize(&n, &n);
	dot = D3DXVec3Dot(&n, &v);
	if (dot < -Radius)
	{
		//OutputDebugString("�����ŏ�����\n");
		return true;
	}

	// Near�ʂ͏��O����

	// Far��
	v1 = wpos[1] - wpos[0];
	v2 = wpos[2] = wpos[0];
	D3DXVec3Cross(&n, &v1, &v2);
	D3DXVec3Normalize(&n, &n);
	dot = D3DXVec3Dot(&n, &v);
	if (dot < -Radius)
	{
		//OutputDebugString("Far�ʂŏ����Ă���\n");
		return true;
	}
	return false;
}

const D3DXMATRIX& GameCamera::view() const
{
	return m_View;
}

const D3DXVECTOR3& GameCamera::position() const
{
	return m_Position;
}

const bool GameCamera::FpsModeNow() const
{
	return m_EnableFpsMode;
}

void GameCamera::EnableFpsMode(bool Enable)
{
	m_EnableFpsMode = Enable;
}

// GameCamera_HelperFunction
void GameCamera::SetViewMatrix()
{
	// �r���[�}�g���N�X�̐ݒ�
	D3DXMatrixLookAtLH(&m_View, &m_Position, &m_Target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_Graphics.SetViewMatrix(m_View);
}

void GameCamera::SetProjectionMatrix()
{
	// �A�X�y�N�g��̌v�Z	
	float aspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	
	// �v���W�F�N�V�����}�g���N�X�̐ݒ�
	D3DXMatrixPerspectiveFovLH(&m_Projection, 1.0f, aspect, 1.0f, 2000.0f);
	m_Graphics.SetProjectionMatrix(m_Projection);
	m_Graphics.SetCameraPosition(m_Position);
}
#pragma endregion GameCamera�̃��\�b�h
