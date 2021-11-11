/*--------------------------------------------------------------

	[GameManager.cpp]
	Author : �o���đ�

	�Q�[���̐i�s���Ǘ�

	���X�|�[��, �r�ŃQ�[�W, ���s

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
	static bool g_PlayerWinner = false; // �v���C���[�̏����Ȃ�true
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
	// �Q�[�����I��������A���U���g�V�[���֑J��
	if (m_GameEnd)
	{
		Engine::Get().application()->SetScene<GameScene::Result>();
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
	// �ǂ��炪�����������߂�
	int32_t i = type;
	switch (i)
	{
		// �G�̏���
	case 0:
		g_PlayerWinner = false;
		break;
		// �v���C���[�̏���
	case 1:
		g_PlayerWinner = true;
		break;
	}
}

ResultManager::ResultManager()
{
	// �I�[�f�B�I�̐ݒ�
	auto audio = std::make_unique<ResultAudio>();
	// BGM�̍Đ�
	audio->Begin(g_PlayerWinner);
	
	// �w�i�̒ǉ�
	Engine::Get().application()->GetScene()->AddGameObject<GameBg::ResultBg>(ELayer::LAYER_2D_BG)->Begin(g_PlayerWinner);
}

void ResultManager::Begin()
{
}
