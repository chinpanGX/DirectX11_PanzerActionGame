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
GameCamera::GameCamera() : m_Position(Math::Vector3(0.0f, 5.0f, -8.0f)), m_Target(Math::Vector3(0.0f, 0.0f, 0.0f)), m_Graphics(*Engine::Get().graphics()), m_EnableFpsMode(false)
{
	
}

GameCamera::~GameCamera()
{

}

void GameCamera::Begin()
{

}

void GameCamera::Update()
{
	const auto& pivot = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->pivot();

	// FPS���[�h
	if (m_EnableFpsMode)
	{
		m_Position = pivot.transform().position() + (pivot.transform().GetVector(Transform::Vector::Forward) * pivot.GetFpsOffset());
		m_Target = pivot.transform().position() + (pivot.transform().GetVector(Transform::Vector::Forward) * pivot.GetTargetOffset());
	}
	// TPS���[�h	
	else
	{
		auto offset = Math::Vector3(0.0f, 5.0f, 0.0f);
		m_Position = pivot.transform().position() + (pivot.transform().GetVector(Transform::Vector::Backward) * pivot.GetTpsOffset()) + offset;
		m_Target = pivot.transform().position() + (pivot.transform().GetVector(Transform::Vector::Forward) * pivot.GetTargetOffset());
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

bool GameCamera::IsDrawObject(Math::Vector3 TargetPosition, float Raduis)
{
	return false;
}

DirectX::XMFLOAT4X4 GameCamera::view() const
{
	return m_View;
}

const Math::Vector3 GameCamera::position() const
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
	// �ϊ�
	DirectX::XMVECTOR eye = Math::Vector3::CastXMVECTOR(m_Position);
	DirectX::XMVECTOR force = Math::Vector3::CastXMVECTOR(m_Target);
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	DirectX::XMMATRIX view = DirectX::XMLoadFloat4x4(&m_View);

	// �r���[�}�g���N�X�̐ݒ�
	view = DirectX::XMMatrixLookAtLH(eye, force, up);
	m_Graphics.SetViewMatrix(view);

	// �v�Z���ʂ�ۑ�����
	m_Position = Math::Vector3(eye);
	m_Target = Math::Vector3(force);
	DirectX::XMStoreFloat4x4(&m_View, view);
}

void GameCamera::SetProjectionMatrix()
{
	// �A�X�y�N�g��̌v�Z	
	float aspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	// �ϊ�
	auto proj = DirectX::XMLoadFloat4x4(&m_Projection);

	// �v���W�F�N�V�����}�g���N�X�̐ݒ�
	proj = DirectX::XMMatrixPerspectiveFovLH(1.0f, aspect, 1.0f, 2000.0f);
	m_Graphics.SetProjectionMatrix(proj);
	m_Graphics.SetCameraPosition(Math::Vector3::CastXMFloat3(m_Position));

	// �v�Z���ʂ�ۑ�
	DirectX::XMStoreFloat4x4(&m_Projection, proj);
}
#pragma endregion GameCamera�̃��\�b�h
