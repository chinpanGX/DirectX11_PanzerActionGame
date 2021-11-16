/*--------------------------------------------------------------
	
	[PanzerStateShot.h]
	Author : �o���đ�

	�X�e�[�g�F����

----------------------------------------------------------------*/
#pragma once
#include "PanzerState.h"

namespace State
{
	class Shot final : public PanzerState
	{
	public:
		Shot();
		~Shot();
		void Update(Cpu* pCpu, float deltaTime)override;
	private:
		void PlayAudio(Cpu* pCpu);
	};
}