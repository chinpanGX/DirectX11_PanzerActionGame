/*--------------------------------------------------------------
	
	[OnComponentEvent.cpp]
	Author : o‡ãÄ‘¾

---------------------------------------------------------------*/
#include "MoveComponent.h"
#include "Pawn.h"
#include "Vehicle.h"
#include "Engine.h"
#include "Application.h"
#include "WallBox.h"
#include "Collision.h"
#include "Command.h"
#include "Fps.h"
#include "OnComponentEvent.h"

void OnComponentEventWallBox::BeginOverlap(Pawn * pPawn)
{
	// •Ç‚Æ‚Ì“–‚½‚è”»’è
	auto wallFence = Engine::Get().application()->GetScene()->GetGameObjects<WallBox>(ELayer::LAYER_3D_STAGE);
	for (auto w : wallFence)
	{
		if (Intersect(pPawn->vehicle().GetBoxComponent(0).GetOBB3(), w->GetBoxComponent().GetOBB3()))
		{
			if (Engine::Get().application()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM)->GetNowInput(0))
			{
				pPawn->GetMoveComponent().MoveBackward(pPawn->vehicle().bodyTransform(), Fps::Get().deltaTime);
			}
			if (Engine::Get().application()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM)->GetNowInput(1))
			{
				pPawn->GetMoveComponent().MoveForward(pPawn->vehicle().bodyTransform(), Fps::Get().deltaTime);
			}
		}
	}
}

