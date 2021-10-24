/*------------------------------------------------------------
	
	[PanzerState.h]
	Author : 出合翔太
	
	何もしないステート

--------------------------------------------------------------*/
#pragma once
#include "PanzerState.h"

namespace State
{
	class Stay final : public PanzerState
	{
	public:
		Stay();
		~Stay();
		void Update(Pawn* pPawn, float deltaTime)override;
	};
}