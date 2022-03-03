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

GarageCamera::GarageCamera() : m_Graphics(*Engine::Get().GetGraphics())
{
	m_Position = D3DXVECTOR3(15.2f, 6.5f, 2.3f);
	m_Target = D3DXVECTOR3(-43.3f, 3.0f, 74.8f);

	// ��p�̐ݒ�(60�x)
	m_Angle = Math::ToRadians(60.0f);

	// �A�X�y�N�g��̌v�Z	
	m_Aspect = static_cast<float>(SCREEN_WIDTH / SCREEN_HEIGHT);
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

	auto up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	// �r���[�}�g���N�X�̐ݒ�
	D3DXMatrixLookAtLH(&m_View, &m_Position, &m_Target, &up);
	m_Graphics.SetViewMatrix(m_View);

	// �v���W�F�N�V�����}�g���N�X�̐ݒ�
	D3DXMatrixPerspectiveFovLH(&m_Projection, m_Angle, m_Aspect, 1.0f, 1000.0f);
	m_Graphics.SetProjectionMatrix(m_Projection);

	m_Graphics.SetCameraPosition(m_Position);
}
