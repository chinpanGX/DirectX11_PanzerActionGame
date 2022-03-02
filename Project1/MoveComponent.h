/*--------------------------------------------------------------
	
	[MoveComponent.h]
	Author : 出合翔太

---------------------------------------------------------------*/
#pragma once
#include "Transform.h"
#include <array>

class Vehicle;
class Status;
class MoveComponent final
{
public:
	MoveComponent() = delete;
	MoveComponent(Status& status);
	~MoveComponent();
	void Update(Transform& Transform);

	// アクション
	void MoveForward(Transform & Transform, float DeltaTime);
	void MoveBackward(Transform & Transform, float DeltaTime);
	void RotRight(Transform& Transform, float DeltaTime);
	void RotLeft(Transform& Transform, float DeltaTime);
	void GunUp(Transform& Transform, float DeltaTime);
	void GunDown(Transform& Transform, float DeltaTime);
	void Stop();

	const D3DXVECTOR3& GetVelocity() const;
private:
	Status& m_Status;
	class GameCommand* m_cmd = nullptr;
	D3DXVECTOR3 m_Velocity;
	float m_Speed = 0.0f;			// 速度
	float m_Acceleration = 1.0f; // 加速度
};

