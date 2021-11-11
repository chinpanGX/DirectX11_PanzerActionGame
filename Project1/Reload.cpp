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
	auto& panzer = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->vehicle();
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
	// カメラの情報を取得
	auto camera = Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	DirectX::XMFLOAT4X4 tmp = camera->view();
	// 変換
	DirectX::XMMATRIX view = DirectX::XMLoadFloat4x4(&tmp);

	// Viewの逆行列
	DirectX::XMMATRIX inverseViewMatrix = DirectX::XMMatrixIdentity();
	inverseViewMatrix = DirectX::XMMatrixInverse(nullptr, inverseViewMatrix);
	inverseViewMatrix.r[3].m128_f32[0] = 0.0f;
	inverseViewMatrix.r[3].m128_f32[1] = 0.0f;
	inverseViewMatrix.r[3].m128_f32[2] = 0.0f;

	// 戦車の情報を取得
	auto& pilot = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->pivot();
	// 戦車の位置にエフェクトの位置を合わせる
	m_Transform->position().x = pilot.transform().position().x;
	m_Transform->position().z = pilot.transform().position().z;

	// 座標変換
	DirectX::XMMATRIX scale = Math::Matrix::MatrixScaling(m_Transform->scale());
	DirectX::XMMATRIX rot = Math::Matrix::MatrixRotationQuatrnionRollPitchYaw(m_Transform->rotation());
	DirectX::XMMATRIX trans = Math::Matrix::MatrixTranslation(m_Transform->position());
	DirectX::XMMATRIX world = scale * rot * inverseViewMatrix * trans;
	m_Graphics.SetWorldMatrix(world);

	// マテリアル
	Material m;
	m.Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Graphics.SetMaterial(m);

	// テクスチャの設定
	m_Resource.SetTexture(0, "Reload");

	Effect::Draw();
}
