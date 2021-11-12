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

bool GameCamera::IsDrawObject(const Math::Vector3& TargetPosition, float Raduis)
{
	// マトリクス計算に使う変数
	DirectX::XMMATRIX view, proj, matViewProj, matInvViewProj;

	// 計算用に変換
	view = DirectX::XMLoadFloat4x4(&m_View);
	proj = DirectX::XMLoadFloat4x4(&m_Projection);

	// ビューマトリクスとプロジェクションマトリクスをかける
	matViewProj = view * proj;
	// 逆行列を求める
	matInvViewProj = DirectX::XMMatrixInverse(nullptr, matViewProj);

	// Far面の座標を求める
	DirectX::XMVECTOR farVecPos[4];
	DirectX::XMVECTOR farPos[4];

	//ベクトルのセット
	farVecPos[0] = DirectX::XMVectorSet(-1.0f, 1.0f, 1.0f, 1.0f);	// 左上
	farVecPos[1] = DirectX::XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);	// 右上	
	farVecPos[2] = DirectX::XMVectorSet(-1.0f, -1.0f, 1.0f, 1.0f);	// 左下
	farVecPos[3] = DirectX::XMVectorSet(1.0f, -1.0f, 1.0f, 1.0f);	// 右下

	// 座標変換
	farPos[0] = DirectX::XMVector3TransformCoord(farVecPos[0], matInvViewProj); // 左上
	farPos[1] = DirectX::XMVector3TransformCoord(farVecPos[1], matInvViewProj); // 右上
	farPos[2] = DirectX::XMVector3TransformCoord(farVecPos[2], matInvViewProj); // 左下
	farPos[3] = DirectX::XMVector3TransformCoord(farVecPos[3], matInvViewProj); // 右下

	// ベクトルの計算に使う変数
	DirectX::XMVECTOR toTarget, normal, v1, v2;
	float dot;

	// 計算用に変換
	DirectX::XMVECTOR c = Math::Vector3::CastXMVECTOR(m_Position); // カメラの位置
	DirectX::XMVECTOR t = Math::Vector3::CastXMVECTOR(TargetPosition); // ターゲットの位置
	// カメラとターゲットのオブジェクトのベクトルを計算
	toTarget = DirectX::XMVectorSubtract(c, t);

	// 指数台と当たり判定のチェック
	
	// 左側
	v1 = DirectX::XMVectorSubtract(farPos[0], c); // カメラから左上のベクトル
	v2 = DirectX::XMVectorSubtract(farPos[2], c); // カメラから左下のベクトル		
	// 外積から法線ベクトルを求める
	normal = DirectX::XMVector3Cross(v1, v2);
	// 法線ベクトルを正規化する
	normal = DirectX::XMVector3Normalize(normal);
	// 法線ベクトルと対象のオブジェクトの内積を取る
	dot = DirectX::XMVectorGetX(DirectX::XMVector3Dot(normal, toTarget));
	if (dot < -Raduis)
	{
		return false;
	}

	// 右側
	v1 = DirectX::XMVectorSubtract(farPos[0], c); // カメラから右上のベクトル
	v2 = DirectX::XMVectorSubtract(farPos[1], c); // カメラから右下のベクトル		
	// 外積から法線ベクトルを求める
	normal = DirectX::XMVector3Cross(v1, v2);
	// 法線ベクトルを正規化する
	normal = DirectX::XMVector3Normalize(normal);
	// 法線ベクトルと対象のオブジェクトの内積を取る
	dot = DirectX::XMVectorGetX(DirectX::XMVector3Dot(normal, toTarget));
	if (dot > Raduis)
	{
		return false;
	}

	return true;
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
