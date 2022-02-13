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

void RemainGage::Begin()
{
	m_Gage = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameBg::DrawGage>(ELayer::LAYER_2D_UI);
}

void RemainGage::Update(GameManager* Manager, Pawn * Pawn, int32_t Type)
{
	float cost = Pawn->GetVehicle().GetStatus().cost();
	float nowgage = GetGage(Type) - (cost * 10.0f);
	// �Q�[�W���c���Ă��Ȃ��̂ŁA���X�|�[���ł��Ȃ�
	if (nowgage <= 0.0f)
	{
		nowgage = 0.0f;
		Manager->SetWinner(Type);
		Manager->GameSet(); // �Q�[���I��
	}
	SetGage(nowgage, Type);
}

void RemainGage::SetGage(float gage, int32_t Type)
{
	switch (Type)
	{
		// �v���C���[��
	case 0:
	//case 1:
		m_PlayerGage = gage;
		m_Gage->SetPlayerGage(m_PlayerGage);
		break;
		// �G��
	//case 2:
	//case 3:
	case 1:
		m_EmenyGage = gage;
		m_Gage->SetEnemyGage(m_EmenyGage);
		break;
	}
}

const float RemainGage::GetGage(int32_t Type) const
{
	switch (Type)
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
	m_Render = std::make_unique<Render>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource());
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
	D3DXVECTOR4 frameColor = D3DXVECTOR4(0.3f, 0.8f, 0.8f, 0.7f);

	D3DXVECTOR2 enemyPosition = D3DXVECTOR2(460.0f, 70.0f);
	D3DXVECTOR4 enemyColor = D3DXVECTOR4(1.0f, 0.2f, 0.2f, 1.0f);
	D3DXVECTOR2 playerPosition = D3DXVECTOR2(460.0f, 100.0f);
	D3DXVECTOR4 playerColor = D3DXVECTOR4(0.2f, 0.2f, 1.0f, 1.0f);

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
