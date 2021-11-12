/*--------------------------------------------------------------

	[PanzerState.cpp]
	Author ; �o���đ�

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

// ���݂̃v���C���[�̈ʒu
const D3DXVECTOR3& PanzerState::SearchPlayer() const
{
	D3DXVECTOR3& playerPosition = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->vehicle().bodyTransform().position();
	return playerPosition;
}
