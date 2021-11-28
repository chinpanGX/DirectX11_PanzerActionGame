/*--------------------------------------------------------------
	
	[Enemy.h]
	Author : 出合翔太

---------------------------------------------------------------*/
#pragma once
#include "Cpu.h"

class Graphics;
class Resource;
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
	bool IsDraw() const;
private:
	void OnCollision()override;
	Pause* m_Pause;
	Player* m_Player;
	GameCamera* m_Camera;
	Resource& m_Resource;
	Graphics& m_Graphics;
	bool m_IsNotDraw = false; // 描画しているどうか
};