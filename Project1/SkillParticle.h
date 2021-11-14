/*--------------------------------------------------------------

	[SkillParticle.h]
	スキル用パーティクル
	Author : 出合翔太

---------------------------------------------------------------*/
#pragma once
#include "Effect.h"

class SkillParticle final : public Effect
{
public:
	SkillParticle();
	~SkillParticle();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:
	float m_Time; // 時間計測
};

