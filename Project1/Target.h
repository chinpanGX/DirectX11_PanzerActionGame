/*--------------------------------------------------------------
	
	[Target.h]
	Author : 出合翔太

	チュートリアルの的

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
	bool m_NotDraw = false; // trueで描画しない
	int32_t m_CoolTime = 100; // 描画しない時間
};

