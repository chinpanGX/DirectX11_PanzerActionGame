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
void GameStageSetterFence::Set(Scene * scene)
{
	for (int32_t i = 0; i < 40; i++)
	{
		// 乱数の生成
		float x = (float)myLib::Random::Rand_R(-500, 500);
		float z = (float)myLib::Random::Rand_R(-500, 500);
		float angle = (float)myLib::Random::Rand_R(0, 360);
		
		// 求めた乱数からTransformを設定していく
		D3DXVECTOR3 pos = D3DXVECTOR3(x, 0.0f, z);
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, angle, 0.0f);

		scene->AddGameObject<Fence>(LAYER_3D_STAGE)->transform().Set(pos, D3DXVECTOR3(1.0f,1.0f,1.0f), rot);
	}
}

/*
	BOX型の壁
*/
void GameStageSetterWallBox::Set(Scene * scene)
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
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(Far, size, g_NegUnitZ);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(Near, size, g_UnitZ);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(Right, size, g_UnitX);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(Left, size, g_NegUnitX);				
#if 0
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(30.0f * i, 0.0f, 150.0f), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(-30.0f * i, 0.0f, 150.0f), size);		
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(150.0f, 0.0f, -30.0f * i), size);		
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(-150.0f, 0.0f, -30.0f * i), size);		
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(30.0f * i, 0.0f, -150.0f), size);		
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(-30.0f * i, 0.0f, -150.0f), size);
#endif
	}
}

/*
	サプライ
*/
void GameStageSetterSupply::Set(Scene * scene)
{
	float x = 250.0f;
	D3DXVECTOR3 pos = D3DXVECTOR3(x, 0.0f, 0.0f);
	D3DXVECTOR3 scl = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scene->AddGameObject<Supply>(LAYER_3D_STAGE)->transform().Set(pos, scl, rot);
	pos.x = -x;
	rot.y = D3DXToRadian(180.0f);
	scene->AddGameObject<Supply>(LAYER_3D_STAGE)->transform().Set(pos, scl, rot);
}

void GameStageSetterRock::Set(Scene * scene)
{
	auto size = D3DXVECTOR3(5.0f, 5.0f, 5.0f);


	auto pos = D3DXVECTOR3(0.0f, 5.0f, 200.0f);
	scene->AddGameObject<Rock>(LAYER_3D_STAGE)->transform().Set(pos, size);
}
