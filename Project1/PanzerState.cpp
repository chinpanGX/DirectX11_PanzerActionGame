/*--------------------------------------------------------------

	[PanzerState.cpp]
	Author ; 出合翔太

---------------------------------------------------------------*/
#include "PanzerState.h"
#include "Player.h"
#include "Vehicle.h"
#include "Body.h"
#include "Engine.h"
#include "Application.h"


PanzerState::PanzerState()
{
}

// 現在のプレイヤーの位置
const D3DXVECTOR3& PanzerState::SearchPlayer() const
{
	D3DXVECTOR3& playerPosition = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->vehicle().bodyTransform().position();
	return playerPosition;
}
