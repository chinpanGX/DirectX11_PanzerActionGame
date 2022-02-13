/*-------------------------------------------------------------
	
	[MiniMap.h]
	Author : 出合翔太

	ミニマップの表示

--------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include <memory>
#include <vector>

// プレイヤーのアイコン
class PlayerIcon final
{
public:
	PlayerIcon();
	~PlayerIcon();
	// param name
	// pos = "描画位置", size = "描画サイズ", rot = "回転"
	void Draw(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, float Rot);
private:	
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	Graphics& m_Graphics;
	Resource& m_Resource;
};

// ミニマップ
class Enemy;
class Player;
class Renderer2D;
class MiniMap final : public DefaultObject
{
public:
	MiniMap();
	~MiniMap();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:
	void OtherIconDraw();
	std::vector<std::unique_ptr<Renderer2D>> m_MarkerList;
	std::unique_ptr<PlayerIcon> m_PlayerIcon;
	//ポインタ
	std::vector<Supply*> m_SupplyList;
	Enemy* m_Enemy;
	Player* m_Player;

	// プレイヤーとエネミーの位置
	D3DXVECTOR2 m_PlayerPosition;
	D3DXVECTOR2 m_EnemyPosition;

	// ミニマップの表示関係
	D3DXVECTOR2 m_Position; // ミニマップの位置
	float m_MapSize;		// ミニマップの大きさ
	float m_Shrink;			// 実際のマップに対してミニマップを縮小する倍率
};
