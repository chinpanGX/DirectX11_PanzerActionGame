/*-----------------------------------------------------------

	[PlayerUi.cpp]
	Author : 出合翔太
	プレイヤー側に表示するUI

------------------------------------------------------------*/
#include "Engine.h"
#include "Application.h"
#include "Graphics.h"
#include "Resource.h"
#include "Fps.h"
#include "Pause.h"
#include "Skill.h"
#include "Status.h"
#include "Vehicle.h"
#include "Pivot.h"
#include "Player.h"
#include "GameCamera.h"
#include "PlayerUi.h"

#pragma region DrawSkill_method
DrawSkill::DrawSkill()
{
	m_Render = std::make_unique<Render>(*Engine::Get().graphics(), *Engine::Get().resource());
}

DrawSkill::~DrawSkill()
{
}

void DrawSkill::Begin()
{
	m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);

	// ゲージを増加する量を計算
	float t = m_Player->vehicle().skill().timeToActivateSkill();
	m_Add = m_MaxDrawSize / t * Fps::Get().deltaTime;
}

void DrawSkill::Update()
{
	if (Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->NowPausing()) { return; }

	// まだスキルが使える状態じゃない
	if (m_Player->vehicle().skill().alreadyUseble() == false)
	{
		// ゲージを増やす
		m_DrawSize += m_Add;
	}
}

void DrawSkill::Event()
{
}

void DrawSkill::Draw()
{
	D3DXVECTOR2 pos = D3DXVECTOR2(1450.0f, 940.0f);
	m_Render->Draw(m_MaxDrawSize, pos, D3DXVECTOR4(0.35f, 0.35f, 0.35f, 0.75f));
	m_Render->Draw(m_DrawSize, pos, D3DXVECTOR4(0.7f, 0.7f, 0.1f, 1.0f));
}

void DrawSkill::Reset()
{
	// 描画サイズを０にする
	m_DrawSize = 0.0f;
}
#pragma endregion スキルゲージを描画する

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
	if (Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->NowPausing()) { return; }

	auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	m_Transform->rotation().z += 0.05f;
	// プレイヤーのリロードが完了すれば削除
	if (player->vehicle().status().finishReload() == true)
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
	auto& pivot = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->pivot();
	// 戦車の位置にエフェクトの位置を合わせる
	m_Transform->position().x = pivot.transform().position().x;
	m_Transform->position().z = pivot.transform().position().z;

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
