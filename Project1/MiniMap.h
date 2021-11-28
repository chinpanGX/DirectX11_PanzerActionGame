/*-------------------------------------------------------------
	
	[MiniMap.h]
	Author : 出合翔太

	ミニマップの表示

--------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include <memory>

class Transform;
class PlayerIcon final
{
public:
	PlayerIcon();
	~PlayerIcon();
	void Begin();
	void Update();
	void Draw(D3DXVECTOR2 pos, D3DXVECTOR2 size, float rot);
private:	
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	Graphics& m_Graphics;
	Resource& m_Resource;
};


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
	std::unique_ptr<Renderer2D> m_Bg;
	std::unique_ptr<Renderer2D> m_Map;
	std::unique_ptr<Renderer2D> m_Icon;
	std::unique_ptr<PlayerIcon> m_PlayerIcon;
	Enemy* m_Enemy;
	Player* m_Player;

	D3DXVECTOR2 m_PlayerPosition;
	D3DXVECTOR2 m_EnemyPosition;

	D3DXVECTOR2 m_Position;
	float m_MapSize;
};
