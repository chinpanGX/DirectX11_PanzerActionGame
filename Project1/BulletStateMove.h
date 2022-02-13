/*-----------------------------------------------------------

	[BulletStateMove.h]
	Author : o‡ãÄ‘¾

	’e‚ªˆÚ“®‚·‚é

------------------------------------------------------------*/
#pragma once
#include "State.h"

class BulletStateMove final : public BulletState
{
public:
	BulletStateMove();
	~BulletStateMove();
	void Update(Bullet* Bullet, float DeltaTime)override;
private:
	void Destory(Bullet* Bullet);
};

