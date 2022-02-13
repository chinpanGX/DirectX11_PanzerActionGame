/*--------------------------------------------------------------

	[SkillParticle.cpp]
	スキル用のパーティクル
	Author : 出合翔太

---------------------------------------------------------------*/
#include "Engine.h"
#include "Graphics.h"
#include "Resource.h"
#include "Application.h"
#include "GameCamera.h"
#include "Pause.h"
#include "SkillParticle.h"
#include "Fps.h"

SkillParticle::SkillParticle() : Effect()
{
	m_Transform = AddComponent<Transform>();
	m_Transform->SetScale(10.0f);
	m_Time = 0.0;
}

SkillParticle::~SkillParticle()
{
}

void SkillParticle::Begin()
{
	
}

void SkillParticle::Update()
{
	// ポーズ中かどうか
	if(Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE)->NowPausing()) { return; }
	

	Effect::Update();
}

void SkillParticle::Event()
{
}

void SkillParticle::Draw()
{
	// テクスチャ座標を計算
	float x = Effect::GetFrame() % 4 * (1.0f / 4.0f);
	float y = Effect::GetFrame() / 4 * (1.0f / 4.0f);

	// map&unmap
	Effect::MapAndUnmap(x, y);

	// マトリクスの設定
	auto camera = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	D3DXMATRIX view = camera->GetView();

	// ビューの逆行列
	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view);//逆行列
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;

	// 座標変換
	D3DXMATRIX world, scale, rot, trans;
	Math::Matrix::MatrixScaling(&scale, GetTransform().GetScale());
	Math::Matrix::MatrixTranslation(&trans, GetTransform().GetPosition());
	world = scale * invView * trans;
	m_Graphics.SetWorldMatrix(world);

	// マテリアル
	Material m;
	m.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Graphics.SetMaterial(m);

	// テクスチャの設定
	m_Resource.SetTexture(0, "SkillEffect");

	Effect::Draw();
}