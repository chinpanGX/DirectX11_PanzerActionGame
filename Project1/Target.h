/*--------------------------------------------------------------
	
	[Target.h]
	Author : o‡ãÄ‘¾

	“I

---------------------------------------------------------------*/
#pragma once
#include "Effect.h"

class Target final: public Effect
{
public:
	Target();
	~Target();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:
	bool m_NotDraw = false; // true‚Å•`‰æ‚µ‚È‚¢
	int32_t m_CoolTime = 100; // •`‰æ‚µ‚È‚¢ŠÔ
};

