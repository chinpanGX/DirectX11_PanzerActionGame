/*--------------------------------------------------------------
	
	[BulletComponentEvent.h]
	Author : 出合翔太

	弾の当たり判定

---------------------------------------------------------------*/
#pragma once
#include "IOnComponentEvent.h"

namespace BulletEvent
{
	// 壁
	class OnComponentEventWallBox final : public IOnComponentEventToActor
	{
	public:
		void BeginOverlap(class Actor* pActor)override;
	};

	// フェンス
	class OnComponentEventFence final : public IOnComponentEventToActor
	{
	public:
		void BeginOverlap(class Actor* pActor)override;
	};
}
