/*--------------------------------------------------------------

	[MuzzleFlash.h]
	Author : 出合翔太

	マズルフラッシュのエフェクト

---------------------------------------------------------------*/
#pragma once
#include "Effect.h"

class MuzzleFlash final : public Effect
{
public:
	MuzzleFlash();
	~MuzzleFlash();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};

