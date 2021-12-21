/*--------------------------------------------------------------

	[PanzerStateShot.cpp]
	Author : �o���đ�

	�X�e�[�g�F����

----------------------------------------------------------------*/
#include "Vehicle.h"
#include "Enemy.h"
#include "Reload.h"
#include "Pivot.h"
#include "PanzerStateShot.h"
#include "Engine.h"
#include "Application.h"
#include "Resource.h"
#include "PanzerStateStay.h"
#include "Body.h"
#include "Player.h"

State::Shot::Shot()
{
	
}

State::Shot::~Shot()
{
}

void State::Shot::Begin(Player * pPlayer)
{
	m_Player = pPlayer;
}

void State::Shot::Update(Enemy* pEnemy, float deltaTime)
{
	// �����[�h���I����Ă��Ȃ��Ȃ猂�ĂȂ�
	if (pEnemy->reload().finishReload() == false) 
	{
		// �X�e�[�g�ύX
		pEnemy->ChangeState(std::make_unique<State::Stay>());
	}

	pEnemy->vehicle().Shot(pEnemy->pivot().transform());
	// �I�[�f�B�I��炷
	PlayAudio(pEnemy);
	// �����[�h�J�n
	pEnemy->reload().Begin();

	// �X�e�[�g�ύX
	pEnemy->ChangeState(std::make_unique<State::Stay>());
}

void State::Shot::PlayAudio(Enemy* pEnemy)
{
	// �v���C���[�̈ʒu���擾
	D3DXVECTOR3 playerPos = m_Player->vehicle().bodyTransform().position();
	// CPU�̈ʒu���擾
	D3DXVECTOR3 cpuPos = pEnemy->vehicle().bodyTransform().position();

	// �v���C���[��CPU�Ԃ̋��������,2�{����
	D3DXVECTOR3 length = cpuPos - playerPos;
	float d = 2.0f * D3DXVec3Length(&length);

	// ��Βl�����߁A1.0f��菬��������@
	d = Math::Abs(d) * 0.001f;
	// �{�����[���̍ő�l-�������狁�߂��l
	float volume = 1.0f - d;

	Engine::Get().resource()->AudioPlay("Shot", volume);
}
