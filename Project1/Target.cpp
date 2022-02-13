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
#include "Bullet.h"
#include "Fps.h"

Target::Target()
{
	m_Transform = AddComponent<Transform>();
	m_Collider = AddComponent<Collider>();
}

Target::~Target()
{
}

void Target::Begin()
{
	m_Transform->SetScale(5.0f, 5.0f, 1.0f);
	m_Collider->SetSphere3(*m_Transform, 5.0f);
}

void Target::Update()
{
	// ポーズ中
	if (Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE)->NowPausing()) { return; }
	
	// 弾
	auto bulletList = Engine::Get().GetApplication()->GetScene()->GetGameObjects<Bullet>(ELayer::LAYER_3D_ACTOR);
	for (auto bullet : bulletList)
	{
		if (bullet)
		{
			// 描画している状態のとき
			if (m_NotDraw == false)
			{
				// 衝突検知
				if (Intersect(bullet->GetCollider().GetSphere3(), m_Collider->GetSphere3()))
				{
					// 弾のオブジェクトに通知
					bullet->OnCollisionEnter();
					// 当たったら描画しない
					m_NotDraw = true;
					m_CoolTime = 10.0f; // 時間
				}
			}
		}
	}

	// 描画していない間の処理
	if (m_NotDraw)
	{
		m_CoolTime -= Fps::Get().deltaTime;
		// クールタイムが0なら描画する
		if (m_CoolTime <= 0)
		{
			m_NotDraw = false;
		}
	}
	Actor::UpdateCollision(*m_Collider);
}

void Target::Event()
{
	
}

void Target::Draw()
{
	// 描画が可能なら
	if (!m_NotDraw) 
	{
		// マトリクスの設定
		auto camera = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
		D3DXMATRIX view = camera->GetView();

		// ビューの逆行列
		D3DXMATRIX invView;
		D3DXMatrixInverse(&invView, NULL, &view);//逆行列
		invView._41 = 0.0f;
		invView._42 = 0.0f;
		invView._43 = 0.0f;

		D3DXMATRIX scale, trans;
		Math::Matrix::MatrixScaling(&scale, m_Transform->GetScale());
		Math::Matrix::MatrixTranslation(&trans, m_Transform->GetPosition());
		D3DXMATRIX world = scale * trans;
		m_Graphics.SetWorldMatrix(world);

		// マテリアル
		Material m;
		m.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Graphics.SetMaterial(m);

		// テクスチャの設定
		m_Resource.SetTexture(0, "Target");

		Effect::Draw();
	}
}
