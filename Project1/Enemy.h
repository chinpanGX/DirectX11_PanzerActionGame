/*--------------------------------------------------------------
	
	[Enemy.h]
	Author : èoçá„ƒëæ

---------------------------------------------------------------*/
#pragma once
#include "Cpu.h"

class Pause;
class Player;
class GameCamera;
class PanzerState;
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
private:
	void OnCollision()override;
	Pause* m_Pause;
	Player* m_Player;
	GameCamera* m_Camera;
	class Resource& m_Resource;
};