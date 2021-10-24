/*-----------------------------------------------------------

	[BulletStateMove.cpp]
	Author : 出合翔太

	弾が移動する

------------------------------------------------------------*/
#include "Vehicle.h"
#include "NormalBullet.h"
#include "BulletStateDestory.h"
#include "Engine.h"
#include "Application.h"
#include "Stage.h"
#include "Fence.h"

#include "Target.h"
#include "BulletStateMove.h"

BulletStateMove::BulletStateMove()
{
}

BulletStateMove::~BulletStateMove()
{
}

void BulletStateMove::Update(Bullet * Bullet, float deltaTime)
{
	// 弾の移動
	Math::Vector3& BulletPosition = Bullet->GetTransform().GetPosition();
	// 飛んでいく方向を出す
	Math::Vector3 vector = Bullet->GetDirectionVector();
	// 方向ベクトルを足していく
	BulletPosition += vector * Bullet->GetSpeed() * deltaTime;
	//　当たり判定
	Bullet->OnCollision();
	// 当たり判定以外のインスタンス削除
	Destory(Bullet);
	// 威力の補正値を下げる
	Bullet->DownDDE();
}

// 当たり判定以外のインスタンス削除
void BulletStateMove::Destory(Bullet* Bullet)
{
	Bullet->FrameCountDown();
	// フレーム数が０になる　AND　0.0fより低くなるとき
	if (Bullet->GetFrameZeroFlag() == true || Bullet->GetTransform().GetPosition().y <= 0.0f)
	{
		if (Bullet != nullptr)
		{
			// 消去
			Bullet->ChangeState(std::make_unique<BulletStateDestory>());
		}
	}
}