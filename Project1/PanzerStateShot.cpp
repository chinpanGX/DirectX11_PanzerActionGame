/*--------------------------------------------------------------

	[PanzerStateShot.cpp]
	Author : 出合翔太

	ステート：撃つ

----------------------------------------------------------------*/
#include "Vehicle.h"
#include "Enemy.h"
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

void State::Shot::Begin(Player * Player)
{
	m_Player = Player;
}

void State::Shot::Update(Enemy* Enemy, float DeltaTime)
{
	// リロードが終わっていないなら撃てない
	if (Enemy->GetReload().GetFinishReload() == false) 
	{
		// ステート変更
		Enemy->ChangeState(std::make_unique<State::Stay>());
	}

	Enemy->GetVehicle().Shot(Enemy->GetPivot().GetTransform());
	// オーディオを鳴らす
	PlayAudio(Enemy);
	// リロード開始
	Enemy->GetReload().Begin();

	// ステート変更
	Enemy->ChangeState(std::make_unique<State::Stay>());
}

void State::Shot::PlayAudio(Enemy* Enemy)
{
	// プレイヤーの位置を取得
	D3DXVECTOR3 playerPos = m_Player->GetVehicle().GetBodyTransform().GetPosition();
	// CPUの位置を取得
	D3DXVECTOR3 cpuPos = Enemy->GetVehicle().GetBodyTransform().GetPosition();

	// プレイヤーとCPU間の距離を取り,2倍する
	D3DXVECTOR3 length = cpuPos - playerPos;
	float d = 2.0f * D3DXVec3Length(&length);

	// 絶対値を求め、1.0fより小さくする　
	d = Math::Abs(d) * 0.001f;
	// ボリュームの最大値-距離から求めた値
	float volume = 1.0f - d;

	Engine::Get().GetResource()->AudioPlay("Shot", volume);
}
