/*-------------------------------------------------------------

	[MiniMap.cpp]
	Author : 出合翔太

	ミニマップの表示

--------------------------------------------------------------*/
#include "Engine.h"
#include "Application.h"
#include "Resource.h"
#include "Graphics.h"
#include "Renderer2D.h"
#include "Vehicle.h"
#include "Pivot.h"
#include "Player.h"
#include "Enemy.h"
#include "Supply.h"
#include "MiniMap.h"
#include "Utility.h"

#pragma region _PlayerIcon
PlayerIcon::PlayerIcon() : m_Graphics(*Engine::Get().GetGraphics()), m_Resource(*Engine::Get().GetResource())
{
	Vertex3D vertex[4];
	vertex[0].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	vertex[1].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	vertex[2].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
	vertex[3].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	for (int i = 0; i < 4; i++)
	{
		vertex[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[i].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	auto hr = m_Graphics.GetDevice()->CreateBuffer(&bd, &sd, m_VertexBuffer.GetAddressOf());
	ThrowIfFailed(hr, "m_VertexBuffer is Failed");
}

PlayerIcon::~PlayerIcon()
{
}

void PlayerIcon::Draw(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, float Rot)
{
	D3DXMATRIX mat[4];
	D3DXMatrixTranslation(&mat[0], -Size.x, -Size.y, 0.0f); // 左上
	D3DXMatrixTranslation(&mat[0], -Size.x, -Size.y, 0.0f); // 左上
	D3DXMatrixTranslation(&mat[1], Size.x, -Size.y, 0.0f);	// 右上
	D3DXMatrixTranslation(&mat[2], -Size.x, Size.y, 0.0f);	// 左下	
	D3DXMatrixTranslation(&mat[3], Size.x, Size.y, 0.0f);	// 右下
	
	D3DXMATRIX mtrans, mrot, mworld;
	float px[4], py[4];

	// マトリクスの計算
	D3DXMatrixTranslation(&mtrans, Pos.x, Pos.y, 0.0f);
	D3DXMatrixRotationZ(&mrot, Rot);
	for (int i = 0; i < 4; i++)
	{
		mworld = mat[i] *  mrot * mtrans;
		px[i] = mworld._41;
		py[i] = mworld._42;
	}

	// シェーダーの設定
	m_Resource.SetShader("NoLighting");

	// map/unmap
	D3D11_MAPPED_SUBRESOURCE msr;
	m_Graphics.GetDeviceContext()->Map(m_VertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	Vertex3D* vertex = (Vertex3D*)msr.pData;

	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	vertex[1].TexCoord = D3DXVECTOR2(0.5f, 0.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 0.5f);
	vertex[3].TexCoord = D3DXVECTOR2(0.5f, 0.5f);
	for (int i = 0; i < 4; i++)
	{
		vertex[i].Position = D3DXVECTOR3(px[i], py[i], 0.0f);
		vertex[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[i].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	m_Graphics.GetDeviceContext()->Unmap(m_VertexBuffer.Get(), 0);

	//マトリクス設定
	m_Graphics.SetWorldViewProjection2D();

	//頂点バッファ設定
	UINT stride = sizeof(Vertex3D);
	UINT offset = 0;
	m_Graphics.GetDeviceContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);

	//テクスチャ設定
	m_Resource.SetTexture(0, "MiniMapMarker");

	//プリミティブトポロジ設定
	m_Graphics.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	m_Graphics.GetDeviceContext()->Draw(4, 0);
}
#pragma endregion _プレイヤーのアイコン_

#pragma region _MiniMap_
namespace
{
	uint32_t framebg = 0;
	uint32_t mapbg = 1;
	uint32_t othermarker = 2;
}

MiniMap::MiniMap()
{
	m_MarkerList.resize(3);
	m_MarkerList[framebg] = std::make_unique<Renderer2D>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource(), "MiniMapBg");
	m_MarkerList[mapbg] = std::make_unique<Renderer2D>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource(), "Gage");
	m_MarkerList[othermarker] = std::make_unique<Renderer2D>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource(), "MiniMapMarker");
	m_PlayerIcon = std::make_unique<PlayerIcon>();
}

MiniMap::~MiniMap()
{
}

void MiniMap::Begin()
{
	m_SupplyList = Engine::Get().GetApplication()->GetScene()->GetGameObjects<Supply>(ELayer::LAYER_3D_STAGE);
	m_Player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	m_Enemy = Engine::Get().GetApplication()->GetScene()->GetGameObject<Enemy>(ELayer::LAYER_3D_ACTOR);

	// マップの縮小率　1/2倍
	m_Shrink = 0.5f; 
	// マップの大きさ
	m_MapSize = 300.0f;
	// マップの位置
	m_Position = D3DXVECTOR2(m_MapSize - 50.0f, static_cast<float>(SCREEN_HEIGHT) - m_MapSize + 50.0f);

	// ミニマップの設定
	auto size = D3DXVECTOR2(m_MapSize, m_MapSize);
	m_MarkerList[mapbg]->SetVertex(m_Position, size);

	// 背景の設定
	// 背景テクスチャの大きさ
	size = D3DXVECTOR2(m_MapSize + 20.0f, m_MapSize + 20.0f);
	m_MarkerList[framebg]->SetVertex(m_Position, size);
}

void MiniMap::Update()
{
	// x座標は正負を反転させる
	// プレイヤーの位置
	m_PlayerPosition.x = m_Position.x - m_Player->GetVehicle().GetBodyTransform().GetPosition().x * m_Shrink * -1;
	m_PlayerPosition.y = m_Position.y - m_Player->GetVehicle().GetBodyTransform().GetPosition().z * m_Shrink;

	// エネミーの位置
	m_EnemyPosition.x = m_Position.x - m_Enemy->GetVehicle().GetBodyTransform().GetPosition().x * m_Shrink * -1;
	m_EnemyPosition.y = m_Position.y - m_Enemy->GetVehicle().GetBodyTransform().GetPosition().z * m_Shrink;
}

void MiniMap::Event()
{
}

void MiniMap::Draw()
{	
	// ミニマップの背景枠の描画
	m_MarkerList[framebg]->Draw();

	// マップの背景の描画
	m_MarkerList[mapbg]->Draw(0.5f);

	// プレイヤー以外のアイコンの描画
	OtherIconDraw();

	// プレイヤーの描画
	auto size = D3DXVECTOR2(20.0f, 20.0f);
	m_PlayerIcon->Draw(m_PlayerPosition, size, m_Player->GetPivot().GetTransform().GetRotation().y);
}

void MiniMap::OtherIconDraw()
{
	auto texmin = D3DXVECTOR2(0.5f, 0.0f);
	auto texmax = D3DXVECTOR2(1.0f, 0.5f);

	for (auto supply : m_SupplyList)
	{
		// ミニマップの描画する位置
		D3DXVECTOR2 pos;
		pos.x = m_Position.x - supply->GetTransform().GetPosition().x * m_Shrink;
		pos.y = m_Position.y - supply->GetTransform().GetPosition().z * m_Shrink;
		// アイコンの大きさ
		auto size = D3DXVECTOR2(30.0f, 30.0f);

		// 描画
		m_MarkerList[othermarker]->Draw(pos, size, texmin, texmax);
	}

	// 敵を描画しているかチェック
	if (m_Enemy->IsDraw())
	{
		// 描画しているなら、ミニマップに映す
		texmin = D3DXVECTOR2(0.0f, 0.5f);
		texmax = D3DXVECTOR2(0.5f, 1.0f);
		// アイコンの大きさ
		auto size = D3DXVECTOR2(20.0f, 20.0f);

		// 描画
		m_MarkerList[othermarker]->Draw(m_EnemyPosition, size, texmin, texmax);
	}
}
#pragma endregion _ミニマップ_