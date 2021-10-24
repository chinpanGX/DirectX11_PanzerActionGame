/*--------------------------------------------------------------

	[GameManager.cpp]
	Author : 出合翔太

	ゲームの進行を管理

	リスポーン, 殲滅ゲージ, 勝敗

---------------------------------------------------------------*/
#include "AudioManager.h"
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
	static bool g_PlayerWinner = false; // プレイヤーの勝利ならtrue
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
	// ゲームが終了したら、リザルトシーンへ遷移
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
	// どちらが勝ったか決める
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
	// オーディオの設定
	auto audio = std::make_unique<ResultAudio>();
	// BGMの再生
	audio->Begin(g_PlayerWinner);
	
	// 背景の追加
	Engine::Get().GetApplication()->GetScene()->AddGameObject<GameBg::ResultBg>(ELayer::LAYER_2D_BG)->Begin(g_PlayerWinner);
}

void ResultManager::Begin()
{
}
