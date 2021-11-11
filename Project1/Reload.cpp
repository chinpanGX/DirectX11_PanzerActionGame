/*--------------------------------------------------------------

	[Reload.cpp]
	Author : 出合翔太

	リロード中に描画するUI

--------------------------------------------------------------*/
#include "Reload.h"
#include "Engine.h"
#include "Graphics.h"
#include "Application.h"
#include "Resource.h"
#include "GameCamera.h"
#include "Panzer.h"
#include "Vehicle.h"
#include "Player.h"
#include "Pivot.h"
#include "Pause.h"

Reload::Reload() : Effect()
{
	m_Transform = Actor::AddComponent<Transform>();
}

Reload::~Reload()
{
}

void Reload::Begin()
{
	m_Transform->Begin();
}

void Reload::Update()
{
	auto pause = Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->GetEnable();
	if (pause) { return; }
	auto& panzer = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->GetVehicle();
	m_Transform->rotation().z += 0.05f;
	if (panzer.GetStatus().GetFinishReload() == true)
	{
		OnDestroy();
	}
}

void Reload::Event()
{
}

void Reload::Draw()
{
	// マトリクスの設定
	auto camera = Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	DirectX::XMMATRIX view = camera->GetInverseView(); // Viewの逆行列
	auto& pilot = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->GetPilot();
	m_Transform->position().x = pilot.transform().position().x;
	m_Transform->position().z = pilot.transform().position().z;
	DirectX::XMMATRIX scale = Math::Matrix::MatrixScaling(m_Transform->scale());
	DirectX::XMMATRIX rot = Math::Matrix::MatrixRotationQuatrnionRollPitchYaw(m_Transform->rotation());
	DirectX::XMMATRIX trans = Math::Matrix::MatrixTranslation(m_Transform->position());
	DirectX::XMMATRIX world = scale * rot * view * trans;
	m_Graphics.SetWorldMatrix(world);

	// マテリアル
	Material m;
	m.Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Graphics.SetMaterial(m);

	// テクスチャの設定
	m_Resource.SetTexture(0, "Reload");

	Effect::Draw();
}
