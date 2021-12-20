/*--------------------------------------------------------------
	
	[Enemy.h]
	Author : èoçá„ƒëæ

---------------------------------------------------------------*/
#pragma once
#include "Pawn.h"
#include <vector>

class Graphics;
class Resource;
class Pause;
class Player;
class GameCamera;
class PanzerState;
class Supply;
class Enemy final : public Pawn
{
public:
	Enemy();
	~Enemy();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void ChangeState(std::unique_ptr<PanzerState> State);
	void Respawn(const D3DXVECTOR3& pos)override;
	void UseSkill();
	bool IsDraw() const;
private:
	void OnCollision()override;
	
	std::vector<Supply*> m_SupplyList;
	std::unique_ptr<class PanzerState> m_State;
	Pause* m_Pause;
	Player* m_Player;
	GameCamera* m_Camera;

	Resource& m_Resource;
	Graphics& m_Graphics;
	bool m_IsNotDraw = false; // ï`âÊÇµÇƒÇ¢ÇÈÇ«Ç§Ç©
};