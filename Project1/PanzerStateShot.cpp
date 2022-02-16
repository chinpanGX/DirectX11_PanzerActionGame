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

void State::Shot::Begin(Player * Player)
{
	m_Player = Player;
}

void State::Shot::Update(Enemy* Enemy, float DeltaTime)
{
	// �����[�h���I����Ă��Ȃ��Ȃ猂�ĂȂ�
	if (Enemy->GetReload().GetFinishReload() == false) 
	{
		// �X�e�[�g�ύX
		Enemy->ChangeState(std::make_unique<State::Stay>());
	}

	Enemy->GetVehicle().Shot(Enemy->GetPivot().GetTransform());
	// �I�[�f�B�I��炷
	PlayAudio(Enemy);
	// �����[�h�J�n
	Enemy->GetReload().Begin();

	// �X�e�[�g�ύX
	Enemy->ChangeState(std::make_unique<State::Stay>());
}

void State::Shot::PlayAudio(Enemy* Enemy)
{
	// �v���C���[�̈ʒu���擾
	D3DXVECTOR3 playerPos = m_Player->GetVehicle().GetBodyTransform().GetPosition();
	// CPU�̈ʒu���擾
	D3DXVECTOR3 cpuPos = Enemy->GetVehicle().GetBodyTransform().GetPosition();

	// �v���C���[��CPU�Ԃ̋��������,2�{����
	D3DXVECTOR3 length = cpuPos - playerPos;
	float d = 2.0f * D3DXVec3Length(&length);

	// ��Βl�����߁A1.0f��菬��������@
	d = Math::Abs(d) * 0.001f;
	// �{�����[���̍ő�l-�������狁�߂��l
	float volume = 1.0f - d;

	Engine::Get().GetResource()->AudioPlay("Shot", volume);
}
