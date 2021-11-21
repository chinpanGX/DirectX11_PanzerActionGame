/*--------------------------------------------------------------

	[PanzerStateShot.cpp]
	Author : 出合翔太

	ステート：撃つ

----------------------------------------------------------------*/
#include "Vehicle.h"
#include "Cpu.h"
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

void State::Shot::Update(Cpu * pCpu, float deltaTime)
{
	pCpu->vehicle().Shot(pCpu->pivot().transform());
	// オーディオを鳴らす
	PlayAudio(pCpu);
	pCpu->ChangeState(std::make_unique<State::Stay>());
}

void State::Shot::PlayAudio(Cpu * pCpu)
{
	// プレイヤーの位置を取得
	auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	D3DXVECTOR3 playerPos = player->vehicle().bodyTransform().position();
	// CPUの位置を取得
	D3DXVECTOR3 cpuPos = pCpu->vehicle().bodyTransform().position();

	// プレイヤーとCPU間の距離を取り,2倍する
	float d = 2.0f * (Math::Sqrt((cpuPos.x - playerPos.x) * (cpuPos.x - playerPos.x) + (cpuPos.y - playerPos.y) *  (cpuPos.y - playerPos.y) + (cpuPos.z - playerPos.z) * (cpuPos.z - playerPos.z)));
	// 絶対値を求める
	d = Math::Abs(d);
	// 1.0fより小さくする　
	d = d * 0.001f;
	// ボリュームの最大値-距離から求めた値
	float volume = 1.0f - d;

	Engine::Get().resource()->AudioPlay("Shot", volume);
}
