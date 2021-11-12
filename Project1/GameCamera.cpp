/*-------------------------------------------------------------
	
	[GameCamera.cpp]
	Author : 出合翔太

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

	// FPSモード
	if (m_EnableFpsMode)
	{
		m_Position = pivot.transform().position() + (pivot.transform().GetVector(Transform::Vector::Forward) * pivot.GetFpsOffset());
		m_Target = pivot.transform().position() + (pivot.transform().GetVector(Transform::Vector::Forward) * pivot.GetTargetOffset());
	}
	// TPSモード	
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
	// ビューマトリクスの設定
	SetViewMatrix();

	// プロジェクションマトリクスの設定
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
	// 変換
	DirectX::XMVECTOR eye = Math::Vector3::CastXMVECTOR(m_Position);
	DirectX::XMVECTOR force = Math::Vector3::CastXMVECTOR(m_Target);
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	DirectX::XMMATRIX view = DirectX::XMLoadFloat4x4(&m_View);

	// ビューマトリクスの設定
	view = DirectX::XMMatrixLookAtLH(eye, force, up);
	m_Graphics.SetViewMatrix(view);

	// 計算結果を保存する
	m_Position = Math::Vector3(eye);
	m_Target = Math::Vector3(force);
	DirectX::XMStoreFloat4x4(&m_View, view);
}

void GameCamera::SetProjectionMatrix()
{
	// アスペクト比の計算	
	float aspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	// 変換
	auto proj = DirectX::XMLoadFloat4x4(&m_Projection);

	// プロジェクションマトリクスの設定
	proj = DirectX::XMMatrixPerspectiveFovLH(1.0f, aspect, 1.0f, 2000.0f);
	m_Graphics.SetProjectionMatrix(proj);
	m_Graphics.SetCameraPosition(Math::Vector3::CastXMFloat3(m_Position));

	// 計算結果を保存
	DirectX::XMStoreFloat4x4(&m_Projection, proj);
}
#pragma endregion GameCameraのメソッド
