/*--------------------------------------------------------------
	
	[Target.h]
	Author : �o���đ�

	�`���[�g���A���̓I

---------------------------------------------------------------*/
#pragma once
#include "Effect.h"

namespace Billboard
{
	class Target final : public Effect
	{
	public:
		Target();
		~Target();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
	private:
		float m_CoolTime = 100.0f; // �`�悵�Ȃ�����
		bool m_NotDraw = false; // true�ŕ`�悵�Ȃ�
	};
}