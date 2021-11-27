/*-----------------------------------------------------------

	[GarageCamera.cpp]
	Author : �o���đ�

	��ԑq�ɂ̃J����

------------------------------------------------------------*/
#include "Engine.h"
#include "Graphics.h"
#include "Application.h"
#include "GarageCamera.h"
#include "Input.h"

GarageCamera::GarageCamera() : m_Graphics(*Engine::Get().graphics())
{
	m_Position = D3DXVECTOR3(15.2f, 6.5f, 2.3f);
	m_Target = D3DXVECTOR3(-43.3f, 3.0f, 74.8f);
}

GarageCamera::~GarageCamera()
{
}

void GarageCamera::Begin()
{
	
}

void GarageCamera::Update()
{
	
}

void GarageCamera::Event()
{
}

void GarageCamera::Draw()
{
	// �r���[�}�g���N�X�̐ݒ�
	D3DXMatrixLookAtLH(&m_View, &m_Position, &m_Target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_Graphics.SetViewMatrix(m_View);

	// ��p�̐ݒ�(60�x)
	float angle = Math::ToRadians(60.0f);

	// �A�X�y�N�g��̌v�Z	
	float aspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	// �v���W�F�N�V�����}�g���N�X�̐ݒ�
	D3DXMatrixPerspectiveFovLH(&m_Projection, angle, aspect, 1.0f, 1000.0f);
	m_Graphics.SetProjectionMatrix(m_Projection);

	m_Graphics.SetCameraPosition(m_Position);
}
