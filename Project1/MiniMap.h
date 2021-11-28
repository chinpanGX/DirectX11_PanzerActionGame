/*-------------------------------------------------------------
	
	[MiniMap.h]
	Author : 出合翔太

	ミニマップの表示

--------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include <memory>

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
	Enemy* m_Enemy;
	Player* m_Player;

	D3DXVECTOR2 m_PlayerPosition;
	D3DXVECTOR2 m_EnemyPosition;

	D3DXVECTOR2 m_Position;
	float m_Radius;
};

