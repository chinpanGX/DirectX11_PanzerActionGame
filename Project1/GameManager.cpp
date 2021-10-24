/*--------------------------------------------------------------

	[GameManager.cpp]
	Author : 出合翔太

	ゲームの進行を管理

	リスポーン, 殲滅ゲージ, 勝敗

---------------------------------------------------------------*/
#include "Manager.h"
#include "Spawn.h"
#include "Gage.h"
#include "Player.h"
#include "Vehicle.h"
#include "Engine.h"
#include "Application.h"
#include "Audio.h"
#include "Engine.h"
#include "Application.h"
#include "Player.h"
#include "Enemy.h"
#include "GameManager.h"
#include "ResultScene.h"
#include "ResultBg.h"

namespace
{
	static bool g_PlayerWinner = false;
}

GameManager::GameManager()
{
	m_Manager[0] = std::make_unique<GameAudio>();
	m_Manager[1] = std::make_unique<RemainGage>();
	m_Manager[2] = std::make_unique<Respawn>();
}

GameManager::~GameManager()
{
	
}

void GameManager::Begin()
{
}

void GameManager::Update()
{
	if (m_GameEnd)
	{
		Engine::Get().GetApplication()->SetScene<GameScene::Result>();
	}
}

void GameManager::Event()
{
}

void GameManager::Draw()
{
}

void GameManager::BeginEvent(Pawn * pawn, int32_t Id)
{
	m_Manager[1]->Update(this, pawn, Id);
	m_Manager[2]->Update(this, pawn, Id);
}

void GameManager::GameSet()
{
	m_GameEnd = true;
}

const bool GameManager::GetGameEnd() const
{
	return m_GameEnd;
}


void GameManager::SetWinner(int32_t type)
{
	int32_t i = type;
	switch (i)
	{
		// 敵の勝利
	case 0:
		g_PlayerWinner = false;
		break;
		// プレイヤーの勝利
	case 1:
		g_PlayerWinner = true;
		break;
	}
}

ResultManager::ResultManager()
{
	auto mgr = std::make_unique<ResultAudio>();
	mgr->Begin(g_PlayerWinner);
	Engine::Get().GetApplication()->GetScene()->AddGameObject<GameBg::ResultBg>(ELayer::LAYER_2D_BG)->Begin(g_PlayerWinner);
}

void ResultManager::Begin()
{
}
