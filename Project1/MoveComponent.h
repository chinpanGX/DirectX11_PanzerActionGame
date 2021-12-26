/*--------------------------------------------------------------
	
	[MoveComponent.h]
	Author : �o���đ�

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
	void Update(Transform& transform);

	// �A�N�V����
	void MoveForward(Transform & transform, float deltaTime);
	void MoveBackward(Transform & transform, float deltaTime);
	void RotRight(Transform& transform, float deltaTime);
	void RotLeft(Transform& transform, float deltaTime);
	void GunUp(Transform& transform, float deltaTime);
	void GunDown(Transform& transform, float deltaTime);
	void Stop();

	D3DXVECTOR3& velocity() ;
private:
	Status& m_Status;
	class GameCommand* m_cmd = nullptr;
	D3DXVECTOR3 m_Velocity;
	float m_Speed = 0.0f;			// ���x
	float m_Acceleration = 1.0f; // �����x
};

