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

Billboard::MuzzleFlash::MuzzleFlash()
{
	m_Transform = AddComponent<Transform>();
}

Billboard::MuzzleFlash::~MuzzleFlash()
{
}

void Billboard::MuzzleFlash::Begin()
{
	m_Transform->Begin();
}

void Billboard::MuzzleFlash::Update()
{
	if(Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE)->NowPausing()) { return; }
	
	Effect::Update();
	// フレーム数が16になったら消去
	if (Effect::GetFrame() >= 16)
	{
		OnDestroy();
	}
}

void Billboard::MuzzleFlash::Event()
{
}

void Billboard::MuzzleFlash::Draw()
{
	// テクスチャ座標を計算
	float x = Effect::GetFrame() % 4 * (1.0f / 4.0f);
	float y = Effect::GetFrame() / 4 * (1.0f / 4.0f);

	// map&unmap
	Effect::MapAndUnmap(x, y);

	// マトリクスの設定
	// カメラの情報を取得する
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

	// テクスチャの設定
	m_Resource.SetTexture(0, "Billboard::Explosion");
	
	Effect::Draw();
}
