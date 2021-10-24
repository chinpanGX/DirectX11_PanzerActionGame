/*--------------------------------------------------------------
	
	[Enemy.h]
	Author : èoçá„ƒëæ

---------------------------------------------------------------*/
#pragma once
#include "Pawn.h"

class PanzerState;
class Enemy final : public Pawn
{
public:
	Enemy();
	~Enemy();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void ChangeState(std::unique_ptr<PanzerState> State)override;
	void Respawn(const Math::Vector3& pos)override;
private:
	void OnCollision()override;
	std::unique_ptr<PanzerState> m_State;
};