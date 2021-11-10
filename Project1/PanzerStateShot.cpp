/*--------------------------------------------------------------

	[PanzerStateShot.cpp]
	Author : �o���đ�

	�X�e�[�g�F����

----------------------------------------------------------------*/
#include "Vehicle.h"
#include "Pawn.h"
#include "Pivot.h"
#include "PanzerStateShot.h"
#include "Engine.h"
#include "Application.h"
#include "Resource.h"
#include "Reload.h"
#include "PanzerStateStay.h"
#include "Body.h"
#include "Player.h"

State::Shot::Shot()
{
}

State::Shot::~Shot()
{
}

void State::Shot::Update(Pawn * pPawn, float deltaTime)
{
	pPawn->GetVehicle().Shot(pPawn->GetPilot().GetTransform());
	OnSound(pPawn);
	auto effect = Engine::Get().GetApplication()->GetScene()->AddGameObject<Reload>(ELayer::LAYER_2D_EFFECT);
	Math::Vector3 offset = pPawn->GetPilot().GetTransform().position() + Math::Vector3(0.0f, 3.0f, 0.0f);
	effect->GetTransform().position(offset);
	pPawn->ChangeState(std::make_unique<State::Stay>());
}

void State::Shot::OnSound(Pawn * pPawn)
{
	// �v���C���[�̈ʒu���擾
	auto player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	Math::Vector3 playerPos = player->GetVehicle().GetBodyTransform().position();
	// CPU�̈ʒu���擾
	Math::Vector3 cpuPos = pPawn->GetVehicle().GetBodyTransform().position();

	// �v���C���[��CPU�Ԃ̋��������,2�{����
	float d = 2.0f * (Math::Sqrt((cpuPos.x - playerPos.x) * (cpuPos.x - playerPos.x) + (cpuPos.y - playerPos.y) *  (cpuPos.y - playerPos.y) + (cpuPos.z - playerPos.z) * (cpuPos.z - playerPos.z)));
	// ��Βl�����߂�
	d = Math::Abs(d);
	// 1.0f��菬��������@
	d = d * 0.001f;
	// �{�����[���̍ő�l-�������狁�߂��l
	float volume = 1.0f - d;

	Engine::Get().GetResource()->AudioPlay("Shot", volume);
}
