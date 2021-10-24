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


Explosion::Explosion() : Effect()
{
	m_Transform = Actor::AddComponent<Transform>();
}

Explosion::~Explosion()
{
}

void Explosion::Begin()
{
	m_Transform->SetScale(3.0f, 3.0f, 0.0f);
}

void Explosion::Update()
{
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
	m_Resource.SetShader("NoLighting");

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

	// マテリアル
	Material m;
	m.Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Graphics.SetMaterial(m);

	// テクスチャの設定
	m_Resource.SetTexture(0, "Explosion");
	
	Effect::Draw();
}