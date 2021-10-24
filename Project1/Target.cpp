/*--------------------------------------------------------------
	
	[Target.cpp]
	Author : 出合翔太

---------------------------------------------------------------*/
#include "Target.h"
#include "Engine.h"
#include "Application.h"
#include "Graphics.h"
#include "Resource.h"
#include "GameCamera.h"
#include "Pause.h"
#include "NormalBullet.h"

Target::Target()
{
	m_Transform = Actor::AddComponent<Transform>();
	m_BoxComponent = Actor::AddComponent<BoxComponent>();
}

Target::~Target()
{
}

void Target::Begin()
{
	m_Transform->SetScale(5.0f, 5.0f, 1.0f);
	m_BoxComponent->SetSphere3(*m_Transform, 5.0f);
}

void Target::Update()
{
	auto pause = Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG);
	if (pause->GetEnable()) { return; }
	// ターゲット
	auto Bullet = Engine::Get().GetApplication()->GetScene()->GetGameObject<NormalBullet>(ELayer::LAYER_3D_ACTOR);
	if(Bullet)
	{
		if (m_NotDraw == false)
		{
			if (Intersect(Bullet->GetBoxComponent().GetSphere3(), m_BoxComponent->GetSphere3()))
			{
				Bullet->OnCollisionEnter();
				// 当たったら描画しない
				m_NotDraw = true;
				m_CoolTime = 100; // 時間
			}
		}
	}

	if (m_NotDraw)
	{
		m_CoolTime--;
		// クールタイムが0なら描画する
		if (m_CoolTime <= 0)
		{
			m_NotDraw = false;
		}
	}
	Actor::UpdateCollision(*m_BoxComponent);
}

void Target::Event()
{
	
}

void Target::Draw()
{
	if (!m_NotDraw)
	{
		// マトリクスの設定
		auto camera = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);

		DirectX::XMMATRIX scale = Math::Matrix::MatrixScaling(m_Transform->GetScale());
		DirectX::XMMATRIX trans = Math::Matrix::MatrixTranslation(m_Transform->GetPosition());
		DirectX::XMMATRIX world = scale * trans;
		m_Graphics.SetWorldMatrix(world);

		// マテリアル
		Material m;
		m.Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Graphics.SetMaterial(m);

		// テクスチャの設定
		m_Resource.SetTexture(0, "Target");

		Effect::Draw();
		m_BoxComponent->SystemDraw();
	}
}
