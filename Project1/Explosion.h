/*-----------------------------------------------------------
	
	[Billboard::Explosion.h]
	Author : �o���đ�

	�����G�t�F�N�g

------------------------------------------------------------*/
#pragma once
#include "Effect.h"

namespace Billboard
{
	class Explosion : public Effect
	{
	public:
		Explosion();
		~Explosion();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
	};
}
