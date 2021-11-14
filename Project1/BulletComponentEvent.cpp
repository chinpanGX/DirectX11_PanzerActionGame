/*--------------------------------------------------------------

	[BulletComponentEvent.cpp]
	Author : �o���đ�

	�e�̓����蔻��

---------------------------------------------------------------*/
#include "Engine.h"
#include "Application.h"
#include "WallBox.h"
#include "Fence.h"
#include "BulletComponentEvent.h"
#include <vector>

void BulletEvent::OnComponentEventWallBox::BeginOverlap(Actor * pActor)
{
	auto list = Engine::Get().application()->GetScene()->GetGameObjects<WallBox>(ELayer::LAYER_3D_STAGE);
	for (auto i : list)
	{
		if (Intersect(pActor->collider().GetAABB3(), i->collider().GetAABB3()))
		{
			pActor->OnCollisionEnter();
			i->OnCollisionEnter();
		}
	}
}

void BulletEvent::OnComponentEventFence::BeginOverlap(Actor * pActor)
{
	// �t�F���X
	std::vector<Fence*> fenceList = Engine::Get().application()->GetScene()->GetGameObjects<Fence>(ELayer::LAYER_3D_STAGE);
	for (Fence* fence : fenceList)
	{
		if (Intersect(pActor->collider().GetAABB3(), fence->collider().GetAABB3()))
		{
			pActor->OnCollisionEnter();
			fence->OnCollisionEnter();
		}
	}
}