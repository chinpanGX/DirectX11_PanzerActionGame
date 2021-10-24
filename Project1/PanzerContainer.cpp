/*--------------------------------------------------------------

	[PanzerContainer.cpp]
	Author : 出合翔太

	戦車のデータを持っているコンテナ

---------------------------------------------------------------*/
#include "Cost.h"
#include "Parameters.h"
#include "PanzerContainer.h"
#include "Vehicle.h"
#include "PanzerList.h"
#include "Application.h"
#include "myLib.h"
#include "Shadow.h"
#include "Factory.h"
#include "PanzerNameList.h"

std::string PanzerContainer::m_PlayerofSelectedPanzer; // プレイヤーの選択した戦車を格納
std::string PanzerContainer::m_CpuofSelectedPanzer; // 敵が選んだ戦車

PanzerContainer::PanzerContainer() : m_Choose(0)
{
	m_PanzerName = PanzerNameList().Get().GetPanzerList();
}

PanzerContainer::~PanzerContainer()
{
}

void PanzerContainer::Begin()
{
	m_Parameters = std::make_unique<Parameters>();
	m_Number = std::make_unique<Cost>();
	Factory::FVehicle f;
	m_Map[m_PanzerName[0]] = f.Create(m_PanzerName[0]);
	m_Map[m_PanzerName[0]]->SetStartPosition(Math::Vector3(0.0f, 0.0f, 20.0f), Math::Vector3(0.0f, Math::ToRadians(180.0f), 0.0f));
	m_PlayerofSelectedPanzer = "Tiger";
}

void PanzerContainer::Update()
{
	// 戦車の選択が前と違うかどうか
	if (m_PanzerName[m_Choose] != m_PlayerofSelectedPanzer)
	{
		// 前に選択していた戦車のインスタンスは削除する
		m_Map[m_PlayerofSelectedPanzer].reset();
		// 次の戦車をセット
		Factory::FVehicle f;
		m_Map[m_PanzerName[m_Choose]] = f.Create(m_PanzerName[m_Choose]);
		m_Map[m_PanzerName[m_Choose]]->SetStartPosition(Math::Vector3(0.0f, 0.0f, 20.0f), Math::Vector3(0.0f, Math::ToRadians(180.0f), 0.0f));
	}

	// 登録状態を更新する
	m_PlayerofSelectedPanzer = m_PanzerName[m_Choose];
	// パラメータ取得
	m_Cost = m_Map[m_PanzerName[m_Choose]]->GetStatus().GetCost();
	m_Hp = m_Map[m_PanzerName[m_Choose]]->GetStatus().GetHp();
	m_Attack = m_Map[m_PanzerName[m_Choose]]->GetStatus().GetAttack();
	m_Defence = 1.5f * m_Map[m_PanzerName[m_Choose]]->GetStatus().GetDefence();
	m_Speed = 3.0f * m_Map[m_PanzerName[m_Choose]]->GetStatus().GetSpeed();
	m_Reload = 300.0f - (20.0f * m_Map[m_PanzerName[m_Choose]]->GetStatus().GetReloadTime());
}

void PanzerContainer::Event()
{
}

void PanzerContainer::Draw()
{
	// 選択中の戦車
	m_Map[m_PanzerName[m_Choose]]->Draw();
	// コスト
	m_Number->Draw((int32_t)m_Cost);
	// HP
	m_Parameters->Draw(m_Hp * 0.1f, Math::Vector2(1500.0f, 290.0f));
	// 攻撃力
	m_Parameters->Draw(m_Attack, Math::Vector2(1500.0f, 360.0f));
	// 装甲
	m_Parameters->Draw(m_Defence, Math::Vector2(1500.0f, 430.0f));
	// 速度
	m_Parameters->Draw(m_Speed, Math::Vector2(1500.0f, 500.0f));
	// 装填速度
	m_Parameters->Draw(m_Reload, Math::Vector2(1500.0f, 570.0f));
}

void PanzerContainer::SetChooseUp()
{
	m_Choose--;
	if (m_Choose < 0)
	{
		m_Choose = m_PanzerName.size() - 1;
	}
	m_InputButton = 1;
}

void PanzerContainer::SetChooseDown()
{
	m_Choose++;
	if (m_Choose == m_PanzerName.size())
	{
		m_Choose = 0;
	}
	m_InputButton = 2;
}

void PanzerContainer::DecisionofCpuPanzer()
{
	uint32_t rand = myLib::Random::Rand_R(0, m_PanzerName.size());
	//  敵の戦車をランダムで選ぶ
	m_CpuofSelectedPanzer = m_PanzerName[rand];
}

const int32_t PanzerContainer::GetChose() const
{
	return m_Choose;
}

void PanzerContainer::Reset()
{
	m_InputButton = 0;
}

const int32_t PanzerContainer::GetButton() const
{
	return m_InputButton;
}

const std::string & PanzerContainer::StringFindPlayerTag() const
{
	return m_PlayerofSelectedPanzer;
}

const std::string & PanzerContainer::StringFindCpuTag() const
{
	return m_CpuofSelectedPanzer;
}
