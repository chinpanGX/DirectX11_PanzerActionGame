/*----------------------------------------------------------
	
	[BulletStateDestory.h]
	Author : �o���đ�

	�e����������X�e�[�g

-----------------------------------------------------------*/
#pragma once
#include "State.h"

class BulletStateDestory final : public BulletState
{
public:
	~BulletStateDestory();
	void Update(class Bullet* Bullet, float DeltaTime)override;
};

