/*--------------------------------------------------------------
	
	[Enemy.h]
	Author : èoçá„ƒëæ

---------------------------------------------------------------*/
#pragma once
#include "Cpu.h"
#include <vector>

class Graphics;
class Resource;
class Pause;
class Player;
class GameCamera;
class PanzerState;
class Supply;
class Enemy final : public Cpu
{
public:
	Enemy();
	~Enemy();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void ChangeState(std::unique_ptr<PanzerState> State)override;
	void Respawn(const D3DXVECTOR3& pos)override;
	bool IsDraw() const;
private:
	void OnCollision()override;
	
	std::vector<Supply*> m_SupplyList;
	Pause* m_Pause;
	Player* m_Player;
	GameCamera* m_Camera;
	Resource& m_Resource;
	Graphics& m_Graphics;
	bool m_IsNotDraw = false; // ï`âÊÇµÇƒÇ¢ÇÈÇ«Ç§Ç©
};