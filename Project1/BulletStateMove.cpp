/*-----------------------------------------------------------

	[BulletStateMove.cpp]
	Author : �o���đ�

	�e���ړ�����

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
	// �e�̈ړ�
	D3DXVECTOR3& BulletPosition = Bullet->transform().position();
	// ���ł����������o��
	D3DXVECTOR3 vector = Bullet->GetDirectionVector();
	// �����x�N�g���𑫂��Ă���
	BulletPosition += vector * Bullet->GetSpeed() * deltaTime;
	//�@�����蔻��
	Bullet->OnCollision();
	// �������Ă��Ȃ��I�u�W�F�N�g�̃C���X�^���X�폜
	Destory(Bullet);
	// �З͂̕␳�l��������
	Bullet->DownDDE();
}

// �����蔻��ȊO�̃C���X�^���X�폜
void BulletStateMove::Destory(Bullet* Bullet)
{
	Bullet->FrameCountDown();
	// �t���[�������O�ɂȂ�@OR�@0.0f���Ⴍ�Ȃ�Ƃ�
	if (Bullet->GetFrameZeroFlag() == true || Bullet->transform().position().y <= 0.0f)
	{
		if (Bullet != nullptr)
		{
			// ����
			Bullet->ChangeState(std::make_unique<BulletStateDestory>());
		}
	}
}