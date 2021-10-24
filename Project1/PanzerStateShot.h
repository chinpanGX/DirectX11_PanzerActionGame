/*--------------------------------------------------------------
	
	[PanzerStateShot.h]
	Author : 出合翔太

	ステート：撃つ

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
		void Update(Pawn* pPawn, float deltaTime)override;
	private:
		void OnSound(Pawn* pPawn);
	};
}