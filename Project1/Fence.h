/*-----------------------------------------------------------
	
	[Fence.h]
	Author : èoçá„ƒëæ

------------------------------------------------------------*/
#pragma once
#include "StageObject.h"

class Enemy;
class Player;
class GameCamera;
class Fence : public StageObject
{
public:
	Fence();
	~Fence();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:
	void OnCollisionToVehicle(const class Vehicle& Vehicle);

	std::vector<Enemy*> m_EnemyList;
	Player* m_Player;
	GameCamera* m_Camera;
};

