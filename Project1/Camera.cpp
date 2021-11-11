/*-------------------------------------------------------------
	
	[Camera.cpp]
	Author : 出合翔太

--------------------------------------------------------------*/
#include "Graphics.h"
#include "Engine.h"
#include "Application.h"
#include "Camera.h"

#pragma region Camera_method
Camera::Camera() : m_Target(Math::Vector3(0.0f, 0.0f, 0.0f)), m_Graphics(*Engine::Get().graphics())
{
}

void Camera::SetViewMatrix()
{
	// 位置の更新
	DirectX::XMVECTOR eye = DirectX::XMVectorSet(m_Transform->position().x, m_Transform->position().y, m_Transform->position().z, 1.0f);
	DirectX::XMVECTOR force = DirectX::XMVectorSet(m_Target.x, m_Target.y, m_Target.z, 1.0f);
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);

	DirectX::XMMATRIX view = DirectX::XMLoadFloat4x4(&m_View);
	view = DirectX::XMMatrixLookAtLH(eye, force, up);
	m_Graphics.SetViewMatrix(view);
}

void Camera::SetProjectionMatrix()
{
	float aspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	auto proj = DirectX::XMLoadFloat4x4(&m_Projection);
	proj = DirectX::XMMatrixPerspectiveFovLH(1.0f, aspect, 1.0f, 2000.0f);
	m_Graphics.SetProjectionMatrix(proj);
	m_Graphics.SetCameraPosition(Math::Vector3::CastXMFloat3(m_Transform->position()));
}

void Camera::SetTarget(Math::Vector3 Target)
{
	m_Target = Target;
}

Math::Vector3 & Camera::GetTarget()
{
	return m_Target;
}

const DirectX::XMMATRIX Camera::GetView() const
{
	return DirectX::XMLoadFloat4x4(&m_View);
}

const DirectX::XMMATRIX Camera::GetProjection() const
{
	return DirectX::XMLoadFloat4x4(&m_Projection);
}
#pragma endregion Cameraメソッド
