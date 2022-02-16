/*-----------------------------------------------------------

	[BulletStateMove.cpp]
	Author : �o���đ�

	�e���ړ�����

------------------------------------------------------------*/
#include "Vehicle.h"
#include "Bullet.h"
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

void BulletStateMove::Update(Bullet * Bullet, float DeltaTime)
{
	// �e�̈ړ�
	D3DXVECTOR3& BulletPosition = Bullet->GetTransform().GetPosition();
	// ���ł����������o��
	D3DXVECTOR3 vector = Bullet->GetDirectionVector();
	// �����x�N�g���𑫂��Ă���
	BulletPosition += vector * Bullet->GetSpeed() * DeltaTime;
	//�@�����蔻��
	Bullet->OnCollision();
	
	Destory(Bullet);

	// �З͂̕␳�l��������
	Bullet->DownDDE();
}

// �����蔻��ȊO�̃C���X�^���X�폜
void BulletStateMove::Destory(Bullet* Bullet)
{
	// �e���n�ʂƓ���������
	if (Bullet->GetTransform().GetPosition().y <= 0.0f)
	{
		if (Bullet != nullptr)
		{
			// ����
			Bullet->ChangeState(std::make_unique<BulletStateDestory>());
		}
	}
}