/*-----------------------------------------------------------

	[BulletStateDestory.h]
	Author : �o���đ�

	�e����������X�e�[�g

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
	// �G�t�F�N�g���Đ�����
	auto effect = Engine::Get().application()->GetScene()->AddGameObject<Explosion>(ELayer::LAYER_2D_EFFECT);
	effect->transform().position(Bullet->transform().position());
	
	// �C���X�^���X�̍폜
	Bullet->OnDestroy();
}

