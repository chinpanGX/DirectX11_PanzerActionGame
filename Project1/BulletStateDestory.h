/*----------------------------------------------------------
	
	[BulletStateDestory.h]
	Author : 出合翔太

	弾を消去するステート

-----------------------------------------------------------*/
#pragma once
#include "State.h"

class BulletStateDestory final : public BulletState
{
public:
	~BulletStateDestory();
	void Update(class Bullet* Bullet, float deltaTime)override;
};

