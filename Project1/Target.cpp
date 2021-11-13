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
	m_Transform->scale(5.0f, 5.0f, 1.0f);
	m_BoxComponent->SetSphere3(*m_Transform, 5.0f);
}

void Target::Update()
{
	// ポーズ中
	auto pause = Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG);
	if (pause->GetEnable()) { return; }
	
	// 弾
	auto Bullet = Engine::Get().application()->GetScene()->GetGameObject<NormalBullet>(ELayer::LAYER_3D_ACTOR);
	if(Bullet)
	{
		// 描画している状態のとき
		if (m_NotDraw == false)
		{
			// 衝突検知
			if (Intersect(Bullet->GetBoxComponent().GetSphere3(), m_BoxComponent->GetSphere3()))
			{
				// 弾のオブジェクトに通知
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
		auto camera = Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
		D3DXMATRIX view = camera->view();

		// ビューの逆行列
		D3DXMATRIX invView;
		D3DXMatrixInverse(&invView, NULL, &view);//逆行列
		invView._41 = 0.0f;
		invView._42 = 0.0f;
		invView._43 = 0.0f;

		D3DXMATRIX scale, trans;
		Math::Matrix::MatrixScaling(&scale, m_Transform->scale());
		Math::Matrix::MatrixTranslation(&trans, m_Transform->position());
		D3DXMATRIX world = scale * trans;
		m_Graphics.SetWorldMatrix(world);

		// マテリアル
		Material m;
		m.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Graphics.SetMaterial(m);

		// テクスチャの設定
		m_Resource.SetTexture(0, "Target");

		Effect::Draw();
		m_BoxComponent->SystemDraw();
	}
}
