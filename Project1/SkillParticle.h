/*--------------------------------------------------------------

	[SkillParticle.h]
	�X�L���p�p�[�e�B�N��
	Author : �o���đ�

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
	float m_Time; // ���Ԍv��
};

