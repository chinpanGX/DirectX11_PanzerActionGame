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
#include "Pause.h"

Skydome::Skydome() : m_RotationSpeed(0.05f), m_Graphics(*Engine::Get().GetGraphics())
{
	m_Transform = AddComponent<Transform>();
}

Skydome::~Skydome()
{
}

void Skydome::Begin()
{
	m_Transform->position(0.0f, -1.0f, 0.0f);
	m_Transform->scale(0.3f);
}

void Skydome::Update()
{
	auto pause = Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->GetEnable();
	if (pause) { return; }
	m_Transform->rotation().y += Math::ToRadians(m_RotationSpeed);
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
	// カメラの情報を取得する
	auto& camera = *Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	Math::Vector3 pos = camera.GetTransform().position();

	// マトリクス計算
	// 錯覚維持のためにスカイドームがカメラの中心に来るようにする
	DirectX::XMMATRIX world, scale, rot, trans;
	scale = DirectX::XMMatrixScaling(m_Transform->scale().x, m_Transform->scale().y, m_Transform->scale().z);
	rot = DirectX::XMMatrixRotationRollPitchYaw(m_Transform->rotation().x, m_Transform->rotation().y, m_Transform->rotation().z);
	trans = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	world = scale * rot * trans;
	m_Graphics.SetWorldMatrix(world);
}
#pragma endregion privateメンバ関数