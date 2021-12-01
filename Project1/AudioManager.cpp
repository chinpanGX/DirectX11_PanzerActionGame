/*--------------------------------------------------------------
	
	[Manager.cpp]
	Author : 出合翔太

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
#include "Spawn.h"
#include "AudioManager.h"

GameAudio::GameAudio()
{
	
}

GameAudio::~GameAudio()
{
	
}

void GameAudio::Begin()
{
	Player* player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (player)
	{
		std::string name;
		auto resource = Engine::Get().resource();
		int32_t Country = player->vehicle().status().country();
		int32_t r = 0; // 乱数
		// 戦車のステータスの国によって、BGMを変える
		switch (Country)
		{
		case Status::Country::DE:
			r = myLib::Random::Rand_R(1, 3);
			if (r == 1)
			{
				name = "DE01";
			}
			else if (r == 2)
			{
				name = "DE02";
			}
			break;
		case Status::Country::UK:
			name = "UK01";
			break;
		case Status::Country::US:
			r = myLib::Random::Rand_R(1, 3);
			if (r == 1)
			{
				name = "US01";
			}
			else if (r == 2)
			{
				name = "US02";
			}
			break;
		case Status::Country::RU:
			name = "RU01";
			break;
		}

		// オーディオのロードと再生
		resource->AudioLoad(name, true);
		resource->AudioPlay(name, 0.3f);
	}
}

void GameAudio::Update(GameManager * manager, Pawn * pawn, int32_t Type)
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

void ResultAudio::Update(GameManager * manager, Pawn * pawn, int32_t Type)
{
}

void ResultAudio::Begin(bool IsPlayerWin)
{
	std::string name;
	// プレイヤーが勝ったかどうか
	bool f = IsPlayerWin;
	// 勝ち
	if (f == true)
	{
		name = "Win";
	}
	// 負け
	else if(f == false)
	{
		name = "Lose";
	}
	// 登録したオーディオを再生
	Engine::Get().resource()->AudioLoad(name, true);
	Engine::Get().resource()->AudioPlay(name, 0.3f);
}
