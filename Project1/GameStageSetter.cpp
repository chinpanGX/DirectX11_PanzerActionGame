/*--------------------------------------------------------------
	
	[GameStageSetter.cpp]
	Author : 出合翔太

---------------------------------------------------------------*/
#include "Scene.h"
#include "Rock.h"
#include "Fence.h"
#include "WallBox.h"
#include "Supply.h"
#include "GameStageSetter.h"

/*
	柵のオブジェクトの設置する
*/
void GameStageSetterFence::Set(Scene * Scene)
{
	D3DXVECTOR3 size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	// 求めた乱数からTransformを設定していく
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;

	for (int32_t i = 0; i < 10; i++)
	{
		pos	= D3DXVECTOR3(180.0f - (i * 15.0f) , 0.0f, 130.0f);
		rot = D3DXVECTOR3(0.0f, Math::ToRadians(180.0f), 0.0f);
		Scene->AddGameObject<Fence>(LAYER_3D_STAGE)->GetTransform().Set(pos, size, rot);
	}

	for (int32_t i = 0; i < 10; i++)
	{
		pos = D3DXVECTOR3(180.0f - (i * 15.0f), 0.0f, -130.0f);
		rot = D3DXVECTOR3(0.0f, 0.0, 0.0f);
		Scene->AddGameObject<Fence>(LAYER_3D_STAGE)->GetTransform().Set(pos, size, rot);
	}

	for (int32_t i = 0; i < 10; i++)
	{
		pos = D3DXVECTOR3(-150.0f - (i * - 10.0f), 0.0f, 200.0f - (i * 20.0f));
		rot = D3DXVECTOR3(0.0f, Math::ToRadians(45.0f), 0.0f);
		Scene->AddGameObject<Fence>(LAYER_3D_STAGE)->GetTransform().Set(pos, size, rot);
	}
	
	for (int32_t i = 0; i < 15; i++)
	{
		pos = D3DXVECTOR3(-100.0f - (i * -10.0f), 0.0f, -230.0f - (i * -20.0f));
		rot = D3DXVECTOR3(0.0f, Math::ToRadians(330.0f), 0.0f);
		Scene->AddGameObject<Fence>(LAYER_3D_STAGE)->GetTransform().Set(pos, size, rot);
	}	
}

/*
	BOX型の壁
*/
void GameStageSetterWallBox::Set(Scene * Scene)
{
	// サイズは固定
	D3DXVECTOR3 size = D3DXVECTOR3(5.0f, 5.0f, 5.0f);

	// マップ範囲 600.0f*600.0f
	for (int32_t i = 1; i < 59; ++i)
	{
		// 配置する位置を決める
		D3DXVECTOR3 Far = D3DXVECTOR3(-300.0f + 10.0f * i, 0.0f, 290.0f);
		D3DXVECTOR3 Near = D3DXVECTOR3(-300.0f + 10.0f * i, 0.0f, -290.0f);
		D3DXVECTOR3 Right = D3DXVECTOR3(-290.0f, 0.0f, -300.0f + 10.0f * i);
		D3DXVECTOR3 Left = D3DXVECTOR3(290.0f, 0.0f, -300.0f + 10.0f * i);

		// 壁を配置
		Scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(Far, size, g_NegUnitZ);
		Scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(Near, size, g_UnitZ);
		Scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(Right, size, g_UnitX);
		Scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(Left, size, g_NegUnitX);				
	}
}

/*
	サプライ
*/
void GameStageSetterSupply::Set(Scene * Scene)
{
	float x = 250.0f;
	D3DXVECTOR3 pos = D3DXVECTOR3(x, 0.0f, 0.0f);
	D3DXVECTOR3 scl = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scene->AddGameObject<Supply>(LAYER_3D_STAGE)->GetTransform().Set(pos, scl, rot);
	pos.x = -x;
	rot.y = D3DXToRadian(180.0f);
	Scene->AddGameObject<Supply>(LAYER_3D_STAGE)->GetTransform().Set(pos, scl, rot);
}

void GameStageSetterRock::Set(Scene * Scene)
{
	m_Scene = Scene;
	SetBackGround();
}

// 背景用の岩を配置
void GameStageSetterRock::SetBackGround()
{
	Set(-130.0f, 5.0f, 300.0f, 5.0f);
	Set(-250.0f, 6.0f, -330.0f, 16.5f);
	Set(250.0f, 6.0f, -330.0f, 14.5f);
	Set(-600.0f, 3.0, -300.0f, 13.0f);
	Set(-620.0f, 2.5f, 30.0f, 15.0f);	
	Set(380.0f, 30.0f, 300.0f, 30.0f);
	Set(50.0f, 5.0f, 350.0f, 15.0f);

	for (int i = 0; i < m_ObjectCount; i++)
	{
		float angle = static_cast<float>(myLib::Random::Rand_R(0, 360));		
		m_Scene->AddGameObject<Rock>(LAYER_3D_STAGE)->Create("Rock", m_Position[i], m_Size[i], angle);		
	}

	// リセット
	m_ObjectCount = 0;
	m_Position.clear();
	m_Size.clear();

	Set(180.0f, 0.0f, 700.0f, 80.0f);
	Set(-420.0f, 0.0f, -80.0f, 17.0f);
	Set(-340.0f, 0.0f, -400.0f, 28.0f);
	Set(30.0f, 0.0f, -500.0f, 30.0f);

	for (int i = 0; i < m_ObjectCount; i++)
	{
		float angle = static_cast<float>(myLib::Random::Rand_R(0, 360));
		m_Scene->AddGameObject<Rock>(LAYER_3D_STAGE)->Create("Rock02", m_Position[i], m_Size[i], angle);
	}

	m_Position.clear();
	m_Size.clear();
}

void GameStageSetterRock::Set(float x, float y, float z, float size)
{
	m_Position.emplace_back(D3DXVECTOR3(x, y, z));
	m_Size.emplace_back(D3DXVECTOR3(size, size, size));
	m_ObjectCount++;
}
