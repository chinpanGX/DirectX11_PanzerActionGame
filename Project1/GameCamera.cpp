/*-------------------------------------------------------------
	
	[GameCamera.cpp]
	Author : �o���đ�

--------------------------------------------------------------*/
#include "Engine.h"
#include "Application.h"
#include "CameraMode.h"
#include "GameCamera.h"
#include "Player.h"
#include "Pivot.h"

#pragma region CameCamera_method
GameCamera::GameCamera() : m_IsChangeMode(false)
{
	m_Transform = Actor::AddComponent<Transform>();
	m_Mode = std::make_unique<TpsCameraMode>();
}

GameCamera::~GameCamera()
{

}

void GameCamera::Begin()
{
	m_Transform->position(Math::Vector3(0.0f, 5.0f, -8.0f));
}

void GameCamera::Update()
{
	auto& pilot = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->GetPilot();
	m_Mode->Update(this, &pilot);
}

void GameCamera::Event()
{
}

void GameCamera::Draw()
{
	SetViewMatrix();
	SetProjectionMatrix();
}

void GameCamera::ChangeMode(std::unique_ptr<CameraMode> Mode)
{
	m_Mode = std::move(Mode);
}

const DirectX::XMMATRIX GameCamera::GetInverseView() const
{
	DirectX::XMVECTOR vec = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	DirectX::XMMATRIX tmp = DirectX::XMMatrixIdentity();
	
	DirectX::XMVECTOR eye = DirectX::XMVectorSet(m_Transform->position().x, m_Transform->position().y, m_Transform->position().z, 1.0f);
	DirectX::XMVECTOR force = DirectX::XMVectorSet(m_Target.x, m_Target.y, m_Target.z, 1.0f);
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);

	tmp = DirectX::XMMatrixLookAtLH(eye, force, up);
	tmp = DirectX::XMMatrixInverse(&vec, tmp);
	tmp.r[3].m128_f32[0] = 0.0f;
	tmp.r[3].m128_f32[1] = 0.0f;
	tmp.r[3].m128_f32[2] = 0.0f;
	return tmp;
}

void GameCamera::ChangeCameraMode(bool Change)
{
	if (this)
	{
		m_IsChangeMode = Change;
	}
}

const bool GameCamera::GetChageMode() const
{
	return m_IsChangeMode;
}
#pragma endregion GameCamera�̃��\�b�h

// ������J�����O
/*
View,D3DX_PI/4,1.0,100,(float)WINDOW_WIDTH/(float)WINDOW_HEIGHT
D3DXMATRIX* pmView,float Angle,float NearClip,float FarClip,float Aspect
//���E�A�㉺�̕��ʂ��v�Z
{
	D3DXVECTOR3 p1, p2, p3;
	//����
	p1 = D3DXVECTOR3(0, 0, 0);
	p2.x = -FarClip * ((FLOAT)tan(Angle / 2)*Aspect);
	p2.y = -FarClip * (FLOAT)tan(Angle / 2);
	p2.z = FarClip;
	p3.x = p2.x;
	p3.y = -p2.y;
	p3.z = p2.z;
	D3DXPlaneFromPoints(&VFLeftPlane, &p1, &p2, &p3);
	//�E��
	p1 = D3DXVECTOR3(0, 0, 0);
	p2.x = FarClip * ((FLOAT)tan(Angle / 2)*Aspect);
	p2.y = FarClip * (FLOAT)tan(Angle / 2);
	p2.z = FarClip;
	p3.x = p2.x;
	p3.y = -p2.y;
	p3.z = p2.z;
	D3DXPlaneFromPoints(&VFRightPlane, &p1, &p2, &p3);
	//���
	p1 = D3DXVECTOR3(0, 0, 0);
	p2.x = -FarClip * ((FLOAT)tan(Angle / 2)*Aspect);
	p2.y = FarClip * (FLOAT)tan(Angle / 2);
	p2.z = FarClip;
	p3.x = -p2.x;
	p3.y = p2.y;
	p3.z = p2.z;
	D3DXPlaneFromPoints(&VFTopPlane, &p1, &p2, &p3);
	//����
	p1 = D3DXVECTOR3(0, 0, 0);
	p2.x = FarClip * ((FLOAT)tan(Angle / 2)*Aspect);
	p2.y = -FarClip * (FLOAT)tan(Angle / 2);
	p2.z = FarClip;
	p3.x = -p2.x;
	p3.y = p2.y;
	p3.z = p2.z;
	D3DXPlaneFromPoints(&VFBottomPlane, &p1, &p2, &p3);
}
*/
