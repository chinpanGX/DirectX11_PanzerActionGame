/*-----------------------------------------------------------

	[BulletStateDestory.h]
	Author : 出合翔太

	弾を消去するステート

------------------------------------------------------------*/
#include "Bullet.h"
#include "BulletStateDestory.h"
#include "Explosion.h"
#include "Engine.h"
#include "Application.h"

BulletStateDestory::~BulletStateDestory()
{
}

void BulletStateDestory::Update(Bullet * Bullet, float deltaTime)
{
	// エフェクトを再生する
	auto effect = Engine::Get().GetApplication()->GetScene()->AddGameObject<Explosion>(ELayer::LAYER_2D_EFFECT);
	effect->GetTransform().SetPosition(Bullet->GetTransform().GetPosition());
	
	// インスタンスの削除
	Bullet->OnDestroy();
}

