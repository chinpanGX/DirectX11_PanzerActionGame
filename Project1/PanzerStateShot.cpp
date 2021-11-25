/*--------------------------------------------------------------

	[PanzerStateShot.cpp]
	Author : 出合翔太

	ステート：撃つ

----------------------------------------------------------------*/
#include "Vehicle.h"
#include "Cpu.h"
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

void State::Shot::Begin(Player * pPlayer)
{
	m_Player = pPlayer;
}

void State::Shot::Update(Cpu * pCpu, float deltaTime)
{
	// リロードが終わっていないなら撃てない
	if (pCpu->reload().finishReload() == false) 
	{
		// ステート変更
		pCpu->ChangeState(std::make_unique<State::Stay>());
	}

	pCpu->vehicle().Shot(pCpu->pivot().transform());
	// オーディオを鳴らす
	PlayAudio(pCpu);
	// リロード開始
	pCpu->reload().Begin();

	// ステート変更
	pCpu->ChangeState(std::make_unique<State::Stay>());
}

void State::Shot::PlayAudio(Cpu * pCpu)
{
	// プレイヤーの位置を取得
	D3DXVECTOR3 playerPos = m_Player->vehicle().bodyTransform().position();
	// CPUの位置を取得
	D3DXVECTOR3 cpuPos = pCpu->vehicle().bodyTransform().position();

	// プレイヤーとCPU間の距離を取り,2倍する
	D3DXVECTOR3 length = cpuPos - playerPos;
	float d = 2.0f * D3DXVec3Length(&length);

	// 絶対値を求める
	d = Math::Abs(d);
	// 1.0fより小さくする　
	d = d * 0.001f;
	// ボリュームの最大値-距離から求めた値
	float volume = 1.0f - d;

	Engine::Get().resource()->AudioPlay("Shot", volume);
}
