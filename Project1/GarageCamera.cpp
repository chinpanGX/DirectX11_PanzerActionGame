/*-----------------------------------------------------------

	[GarageCamera.cpp]
	Author : 出合翔太

	戦車倉庫のカメラ

------------------------------------------------------------*/
#include "Engine.h"
#include "Graphics.h"
#include "Application.h"
#include "GarageCamera.h"
#include "Input.h"

GarageCamera::GarageCamera() : m_Graphics(*Engine::Get().graphics())
{
	m_Position = Math::Vector3(15.2f, 5.5f, 2.3f);
	m_Target = Math::Vector3(-43.3f, 3.0f, 74.8f);
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
	// 変換
	DirectX::XMVECTOR eye = Math::Vector3::CastXMVECTOR(m_Position);
	DirectX::XMVECTOR force = Math::Vector3::CastXMVECTOR(m_Target);
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	DirectX::XMMATRIX view = DirectX::XMLoadFloat4x4(&m_View);

	// ビューマトリクスの設定
	view = DirectX::XMMatrixLookAtLH(eye, force, up);
	m_Graphics.SetViewMatrix(view);

	// 画角の設定(60度)
	float angle = Math::ToRadians(60.0f);

	// アスペクト比の計算	
	float aspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	// 変換
	auto proj = DirectX::XMLoadFloat4x4(&m_Projection);

	// プロジェクションマトリクスの設定
	proj = DirectX::XMMatrixPerspectiveFovLH(angle, aspect, 1.0f, 1000.0f);
	m_Graphics.SetProjectionMatrix(proj);
	m_Graphics.SetCameraPosition(Math::Vector3::CastXMFloat3(m_Position));
}
