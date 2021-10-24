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
	void Update();

	// アクション
	void MoveForward(Transform & transform, float deltaTime);
	void MoveBackward(Transform & transform, float deltaTime);
	void RotRight(Transform& transform, float deltaTime);
	void RotLeft(Transform& transform, float deltaTime);
	void GunUp(Transform& transform, float deltaTime);
	void GunDown(Transform& transform, float deltaTime);
	
private:
	Status& m_Status;
	float m_Speed = 0.0f;
};

