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
	auto wallFence = Engine::Get().GetApplication()->GetScene()->GetGameObjects<WallBox>(ELayer::LAYER_3D_STAGE);
	for (auto w : wallFence)
	{
		if (Intersect(pPawn->GetVehicle().GetBoxComponent(0).GetAABB3(), w->GetBoxComponent().GetAABB3()))
		{
			if (Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM)->GetNowInput(0))
			{
				pPawn->GetMoveComponent().MoveBackward(pPawn->GetVehicle().GetBodyTransform(), Fps::Get().deltaTime);
			}
			if (Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM)->GetNowInput(1))
			{
				pPawn->GetMoveComponent().MoveForward(pPawn->GetVehicle().GetBodyTransform(), Fps::Get().deltaTime);
			}
		}
	}
}

