/*------------------------------------------------------------

	[Skydome.cpp]
	Author : 出合翔太

-------------------------------------------------------------*/
#include "GameCamera.h"
#include "Resource.h"
#include "Graphics.h"
#include "Application.h"
#include "Engine.h"
#include "Renderer3D.h"
#include "Skydome.h"

Skydome::Skydome() : m_RotationSpeed(0.05f), m_Graphics(*Engine::Get().GetGraphics())
{
	m_Transform = AddComponent<Transform>();
}

Skydome::~Skydome()
{
}

void Skydome::Begin()
{
	m_Camera = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	m_Transform->SetPosition(0.0f, -1.0f, 0.0f);
	m_Transform->SetScale(0.3f);
}

void Skydome::Update()
{
	// スカイドームを回転させて、動いているように見せる
	m_Transform->GetRotation().y += Math::ToRadians(m_RotationSpeed);
}

void Skydome::Event()
{
}

void Skydome::Draw()
{
	GetResource().SetShader("NoLighting");
	// マトリクスの更新
	UpdateMatrix();
	GetResource().SetStaticModel("Sky");	
}

#pragma region private_method
void Skydome::UpdateMatrix()
{
	// カメラの位置を取得する
	D3DXVECTOR3 pos = m_Camera->GetPosition();

	// 錯覚維持のためにスカイドームがカメラの中心に来るようにする
	// マトリクス設定

	// 座標変換
	D3DXMATRIX scale, rot, trans;
	Math::Matrix::MatrixScaling(&scale, m_Transform->GetScale());
	Math::Matrix::MatrixRotationRollPitchYaw(&rot, m_Transform->GetRotation());
	Math::Matrix::MatrixTranslation(&trans, pos);
	D3DXMATRIX world = scale * rot * trans;
	m_Graphics.SetWorldMatrix(world);
}
#pragma endregion privateメンバ関数