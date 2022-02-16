/*--------------------------------------------------------------
	
	[Pivot.h]
	Author : 出合翔太
	
	戦車を操縦

---------------------------------------------------------------*/
#pragma once
#include "Actor.h"

class MoveComponent;
class Vehicle;
class Pivot : public Actor
{
public:
	Pivot() = delete;
	Pivot(Vehicle& Vehicle);
	~Pivot();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void SetStartPosition(D3DXVECTOR3 Position, D3DXVECTOR3 Rot);
  
	const float GetTpsOffset() const;
	const float GetFpsOffset() const;
	const float GetTargetOffset() const;

	// アクション
	void Move();

	MoveComponent& GetMoveComponent()const;
private:
	std::unique_ptr<MoveComponent> m_MoveComponent;
	// 補正をかける値
	D3DXVECTOR3	m_PositionOffset;
	const float m_TspOffset = 20.0f;
	const float m_FpsOffset = 13.0f;
	const float m_TargetOffset = 50.0f;
	Vehicle& m_Vehicle;
};

