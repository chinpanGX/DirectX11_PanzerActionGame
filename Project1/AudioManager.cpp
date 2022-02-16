/*--------------------------------------------------------------
	
	[Manager.cpp]
	Author : �o���đ�

---------------------------------------------------------------*/
#include "GameManager.h"
#include "Engine.h"
#include "Resource.h"
#include "Application.h"
#include "Vehicle.h"
#include "Status.h"
#include "Player.h"
#include "Audio.h"
#include "Gage.h"
#include "SPawn.h"
#include "AudioManager.h"

GameAudio::GameAudio()
{
	
}

GameAudio::~GameAudio()
{
	
}

void GameAudio::Begin()
{
	Player* player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (player)
	{
		std::string name;
		auto resource = Engine::Get().GetResource();
		int32_t Country = player->GetVehicle().GetStatus().GetCountry();
		int32_t r = 0; // ����
		// ��Ԃ̃X�e�[�^�X�̍��ɂ���āABGM��ς���
		switch (Country)
		{
		case Status::Country::DE:
			name = "DE01";
			break;
		case Status::Country::UK:
			name = "UK01";
			break;
		case Status::Country::US:
			name = "US01";
			break;
		case Status::Country::RU:
			name = "RU01";
			break;
		}

		// �I�[�f�B�I�̃��[�h�ƍĐ�
		resource->AudioLoad(name, true);
		resource->AudioPlay(name, 0.3f);
	}
}

void GameAudio::Update(GameManager * Manager, Pawn * Pawn, int32_t Type)
{
}

ResultAudio::ResultAudio()
{
	
}

ResultAudio::~ResultAudio()
{
	
}

void ResultAudio::Begin()
{
}

void ResultAudio::Update(GameManager * Manager, Pawn * Pawn, int32_t Type)
{
}

void ResultAudio::Begin(bool IsPlayerWin)
{
	std::string name;
	// �v���C���[�����������ǂ���
	bool f = IsPlayerWin;
	// ����
	if (f == true)
	{
		name = "Win";
	}
	// ����
	else if(f == false)
	{
		name = "Lose";
	}
	// �o�^�����I�[�f�B�I���Đ�
	Engine::Get().GetResource()->AudioLoad(name, true);
	Engine::Get().GetResource()->AudioPlay(name, 0.3f);
}
