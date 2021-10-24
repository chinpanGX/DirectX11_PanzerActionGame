/*--------------------------------------------------------------

	[MuzzleFlash.cpp]
	Author : 出合翔太

	マズルフラッシュのエフェクト

---------------------------------------------------------------*/
#include "MuzzleFlash.h"
#include "Engine.h"
#include "Graphics.h"
#include "Application.h"
#include "Resource.h"
#include "GameCamera.h"
#include "Pause.h"

MuzzleFlash::MuzzleFlash()
{
	m_Transform = Actor::AddComponent<Transform>();
}

MuzzleFlash::~MuzzleFlash()
{
}

void MuzzleFlash::Begin()
{
	m_Transform->Begin();
}

void MuzzleFlash::Update()
{
	auto pause = Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->GetEnable();
	if (pause) { return; }
	Effect::Update();
	// フレーム数が16になったら消去
	if (Effect::GetFrame() >= 16)
	{
		OnDestroy();
	}
}

void MuzzleFlash::Event()
{
}

void MuzzleFlash::Draw()
{
	// テクスチャ座標を計算
	float x = Effect::GetFrame() % 4 * (1.0f / 4.0f);
	float y = Effect::GetFrame() / 4 * (1.0f / 4.0f);

	// map&unmap
	Effect::MapAndUnmap(x, y);

	// マトリクスの設定
	auto camera = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	DirectX::XMMATRIX view = camera->GetInverseView(); // Viewの逆行列

	DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(m_Transform->GetScale().x, m_Transform->GetScale().y, m_Transform->GetScale().z);
	DirectX::XMMATRIX trans = DirectX::XMMatrixTranslation(m_Transform->GetPosition().x, m_Transform->GetPosition().y, m_Transform->GetPosition().z);
	DirectX::XMMATRIX world = scale * view * trans;
	m_Graphics.SetWorldMatrix(world);

	// テクスチャの設定
	m_Resource.SetTexture(0, "Explosion");
	
	Effect::Draw();
}
