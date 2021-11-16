/*--------------------------------------------------------------
	
	[Enemy.h]
	Author : èoçá„ƒëæ

---------------------------------------------------------------*/
#pragma once
#include "Cpu.h"

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
	class Resource& m_Resource;
};