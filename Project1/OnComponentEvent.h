/*--------------------------------------------------------------

	[OnComponentEvent.h]
	Author : 出合翔太

	当たり判定後のイベント

---------------------------------------------------------------*/
#pragma once
#include "IOnComponentEvent.h"

class OnComponentEventWallBox final : public IOnComponentEventToPawn
{
public:
	void BeginOverlap(class Pawn* pPawn)override;
};