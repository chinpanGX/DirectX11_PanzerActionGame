/*-------------------------------------------------------------

	[IOnCompoennt.h]
	Author : 出合翔太

	当たり判定を取った後のイベントを管理

--------------------------------------------------------------*/
#pragma once

class IOnComponentEventToPawn
{
public:
	virtual ~IOnComponentEventToPawn() {}
	virtual void BeginOverlap(class Pawn* pawn) = 0;
};

class IOnComponentEventToActor
{
public:
	virtual ~IOnComponentEventToActor() {}
	virtual void BeginOverlap(class Actor* pActor) = 0;
};