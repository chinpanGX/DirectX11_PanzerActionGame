/*--------------------------------------------------------------

	[Reload.h]
	Author : o‡ãÄ‘¾

	ƒŠƒ[ƒh’†‚É•`‰æ‚·‚éUI

--------------------------------------------------------------*/
#pragma once
#include "Effect.h"

class Reload : public Effect
{
public:
	Reload();
	~Reload();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};

