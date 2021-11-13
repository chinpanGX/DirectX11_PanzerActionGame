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
	D3DXMATRIX view = camera->view();

	// ビューの逆行列
	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, nullptr, &view);//逆行列
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;

	// 戦車の情報を取得
	auto& pilot = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->pivot();
	// 戦車の位置にエフェクトの位置を合わせる
	m_Transform->position().x = pilot.transform().position().x;
	m_Transform->position().z = pilot.transform().position().z;

	// 座標変換
	D3DXMATRIX scale, rot, trans;
	Math::Matrix::MatrixScaling(&scale, m_Transform->scale());
	Math::Matrix::MatrixRotationRollPitchYaw(&rot, m_Transform->rotation());
	Math::Matrix::MatrixTranslation(&trans, m_Transform->position());
	D3DXMATRIX world = scale * rot * invView * trans;
	m_Graphics.SetWorldMatrix(world);
	
	// マテリアル
	Material m;
	m.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Graphics.SetMaterial(m);

	// テクスチャの設定
	m_Resource.SetTexture(0, "Reload");

	Effect::Draw();
}
