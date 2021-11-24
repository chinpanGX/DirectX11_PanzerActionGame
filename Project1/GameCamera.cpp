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

	// FPSモード
	if (m_EnableFpsMode)
	{
		m_Position = pivot.transform().position() + (pivot.transform().forward() * pivot.GetFpsOffset());
		m_Target = pivot.transform().position() + (pivot.transform().forward() * pivot.GetTargetOffset());
	}
	// TPSモード	
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
	// ビューマトリクスの設定
	SetViewMatrix();

	// プロジェクションマトリクスの設定
	SetProjectionMatrix();
}

bool GameCamera::NotDrawObject(const D3DXVECTOR3& TargetPosition, float Radius)
{
	D3DXMATRIX vp, invvp;

	vp = m_View * m_Projection;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	// far面の座標
	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vpos[1] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	// 座標変換
	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);

	D3DXVECTOR3 v, v1, v2, n;
	float dot;

	// 左側
	// カメラと対象のオブジェクトのベクトル
	v = TargetPosition - m_Position;

	// 法線ベクトルを求める 
	v1 = wpos[0] - m_Position;
	v2 = wpos[2] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);
	D3DXVec3Normalize(&n, &n);
	dot = D3DXVec3Dot(&n, &v);
	if (dot < -Radius)
	{
		//OutputDebugString("左側で消えている\n");
		return true;
	}

	// 右側
	v1 = wpos[1] - m_Position;
	v2 = wpos[3] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);
	D3DXVec3Normalize(&n, &n);
	dot = D3DXVec3Dot(&n, &v);
	if (dot > Radius)
	{
		// OutputDebugString("右側で消えている\n");
		return true;
	}

	// 上側
	v1 = wpos[0] - m_Position;
	v2 = wpos[1] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);
	D3DXVec3Normalize(&n, &n);
	dot = D3DXVec3Dot(&n, &v);
	if (dot > Radius)
	{
		//OutputDebugString("上側で消える\n");
		return true;
	}

	// 下側
	v1 = wpos[2] - m_Position;
	v2 = wpos[3] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);
	D3DXVec3Normalize(&n, &n);
	dot = D3DXVec3Dot(&n, &v);
	if (dot < -Radius)
	{
		//OutputDebugString("下側で消える\n");
		return true;
	}

	// Near面は除外する

	// Far面
	v1 = wpos[1] - wpos[0];
	v2 = wpos[2] = wpos[0];
	D3DXVec3Cross(&n, &v1, &v2);
	D3DXVec3Normalize(&n, &n);
	dot = D3DXVec3Dot(&n, &v);
	if (dot < -Radius)
	{
		//OutputDebugString("Far面で消えている\n");
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
	// ビューマトリクスの設定
	D3DXMatrixLookAtLH(&m_View, &m_Position, &m_Target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_Graphics.SetViewMatrix(m_View);
}

void GameCamera::SetProjectionMatrix()
{
	// アスペクト比の計算	
	float aspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	
	// プロジェクションマトリクスの設定
	D3DXMatrixPerspectiveFovLH(&m_Projection, 1.0f, aspect, 1.0f, 2000.0f);
	m_Graphics.SetProjectionMatrix(m_Projection);
	m_Graphics.SetCameraPosition(m_Position);
}
#pragma endregion GameCameraのメソッド
