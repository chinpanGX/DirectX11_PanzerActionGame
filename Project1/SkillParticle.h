/*--------------------------------------------------------------

	[SkillParticle.h]
	Author : �o���đ�

	�X�L���p�p�[�e�B�N��

---------------------------------------------------------------*/
#pragma once
#include "Effect.h"

namespace Billboard
{
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
}