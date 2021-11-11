/*--------------------------------------------------------------

	[Gage.h]
	Author : �o���đ�

	�r�ŃQ�[�W�̕\��

---------------------------------------------------------------*/
#include "Engine.h"
#include "Application.h"
#include "Command.h"
#include "Graphics.h"
#include "Resource.h"
#include "Renderer2D.h"
#include "Pawn.h"
#include "Vehicle.h"
#include "Status.h"
#include "GameManager.h"
#include "Gage.h"

RemainGage::RemainGage()
{
}

RemainGage::~RemainGage()
{
}

void RemainGage::Update(GameManager* manager, Pawn * pawn, int32_t type)
{
	float cost = pawn->vehicle().GetStatus().GetCost();
	float nowgage = GetGage(type) - (cost * 10.0f);
	// �Q�[�W���c���Ă��Ȃ��̂ŁA���X�|�[���ł��Ȃ�
	if (nowgage <= 0.0f)
	{
		nowgage = 0.0f;
		manager->SetWinner(type);
		manager->GameSet(); // �Q�[���I��
	}
	SetGage(nowgage, type);
}

void RemainGage::SetGage(float gage, int32_t type)
{
	switch (type)
	{
		// �v���C���[��
	case 0:
	//case 1:
		m_PlayerGage = gage;
		Engine::Get().application()->GetScene()->GetGameObject<GameBg::DrawGage>(ELayer::LAYER_2D_UI)->SetPlayerGage(m_PlayerGage);
		break;
		// �G��
	//case 2:
	//case 3:
	case 1:
		m_EmenyGage = gage;
		Engine::Get().application()->GetScene()->GetGameObject<GameBg::DrawGage>(ELayer::LAYER_2D_UI)->SetEnemyGage(m_EmenyGage);
		break;
	}
}

const float RemainGage::GetGage(int32_t type) const
{
	switch (type)
	{
	case 0:
		return m_PlayerGage;
		break;
	case 1:
		return m_EmenyGage;
		break;
	}
	return NULL;
}


GameBg::DrawGage::DrawGage()
{
	m_Render = std::make_unique<Render>(*Engine::Get().graphics(), *Engine::Get().resource());
}

GameBg::DrawGage::~DrawGage()
{
}

void GameBg::DrawGage::Update()
{
}

void GameBg::DrawGage::Event()
{
}

void GameBg::DrawGage::Draw()
{
	// �w�i�̃J���[
	Math::Vector4 frameColor = Math::Vector4(0.3f, 0.8f, 0.8f, 0.7f);

	Math::Vector2 enemyPosition = Math::Vector2(460.0f, 70.0f);
	Math::Vector4 enemyColor = Math::Vector4(1.0f, 0.2f, 0.2f, 1.0f);
	Math::Vector2 playerPosition = Math::Vector2(460.0f, 100.0f);
	Math::Vector4 playerColor = Math::Vector4(0.2f, 0.2f, 1.0f, 1.0f);

	// MAX���
	m_Render->Draw(1000.0f, enemyPosition, frameColor);
	m_Render->Draw(1000.0f, playerPosition, frameColor);

	// ���ۂ̟r�ŃQ�[�W
	m_Render->Draw(m_EmenyGage, enemyPosition, enemyColor);
	m_Render->Draw(m_PlayerGage, playerPosition, playerColor);
}

void GameBg::DrawGage::SetEnemyGage(float f)
{
	m_EmenyGage = f;
}

void GameBg::DrawGage::SetPlayerGage(float f)
{
	m_PlayerGage = f;
}
