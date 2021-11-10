/*-----------------------------------------------------------

	[Explosion.cpp]
	Author : 出合翔太

	爆発エフェクト

------------------------------------------------------------*/
#include "Explosion.h"
#include "Engine.h"
#include "Graphics.h"
#include "Application.h"
#include "Resource.h"
#include "GameCamera.h"
#include "Pause.h"

Explosion::Explosion() : Effect()
{
	m_Transform = Actor::AddComponent<Transform>();
	m_Transform->scale(10.0f);
}

Explosion::~Explosion()
{
}

void Explosion::Begin()
{
	
}

void Explosion::Update()
{
	// ポーズ中かどうか
	auto pause = Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->GetEnable();
	if (pause) { return; }

	Effect::Update();
	// フレーム数が16になったら消去
	if (Effect::GetFrame() >= 16)
	{
		OnDestroy();
	}
}

void Explosion::Event()
{
}

void Explosion::Draw()
{	
	// テクスチャ座標を計算
	float x = Effect::GetFrame() % 4 * (1.0f / 4.0f);
	float y = Effect::GetFrame() / 4 * (1.0f / 4.0f);
	
	// map&unmap
	Effect::MapAndUnmap(x, y);
	
	// マトリクスの設定
	auto camera = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	DirectX::XMMATRIX view = camera->GetInverseView(); // Viewの逆行列
	
	DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(m_Transform->scale().x, m_Transform->scale().y, m_Transform->scale().z);	
	DirectX::XMMATRIX trans = DirectX::XMMatrixTranslation(m_Transform->position().x, m_Transform->position().y, m_Transform->position().z);
	DirectX::XMMATRIX world = scale * view * trans;
	m_Graphics.SetWorldMatrix(world);

	// マテリアル
	Material m;
	m.Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Graphics.SetMaterial(m);

	// テクスチャの設定
	m_Resource.SetTexture(0, "Explosion");
	
	Effect::Draw();
}