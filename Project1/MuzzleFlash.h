/*--------------------------------------------------------------

	[MuzzleFlash.h]
	Author : �o���đ�

	�}�Y���t���b�V���̃G�t�F�N�g

---------------------------------------------------------------*/
#pragma once
#include "Effect.h"

namespace Billboard
{
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
}
