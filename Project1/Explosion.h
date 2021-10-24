/*-----------------------------------------------------------
	
	[Explosion.h]
	Author : 出合翔太

	爆発エフェクト

------------------------------------------------------------*/
#pragma once
#include "Effect.h"

class Explosion : public Effect
{
public:
	Explosion();
	~Explosion();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};

