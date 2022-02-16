/*--------------------------------------------------------------

	[TutorialStageSetter.cpp]
	Author : 出合翔太

	チュートリアルステージのオブジェクトを設置する

---------------------------------------------------------------*/
#include "Scene.h"
#include "WallBox.h"
#include "Target.h"
#include "Supply.h"
#include "TutorialStageSetter.h"

/*
	BOX型の壁
 */
void TutorialStageSetterWall::Set(Scene * Scene)
{
	// サイズの設定
	D3DXVECTOR3 size = D3DXVECTOR3(3.0f, 3.0f, 3.0f);

	// GameObjectのリストに追加
	for (int32_t i = 0; i < 20; ++i)
	{
		Scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(8.0f * i, 0.0f, 0.0f), size, g_NegUnitZ);
		Scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(-8.0f * i, 0.0f, 0.0f), size, g_NegUnitZ);
		Scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(150.0f, 0.0f, -12.0f * i), size, g_NegUnitX);
		Scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(-150.0f, 0.0f, -12.0f * i), size, g_UnitX);
		Scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(8.0f * i, 0.0f, -200.0f), size, g_UnitZ);
		Scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(-8.0f * i, 0.0f, -200.0f), size, g_UnitZ);
	}
}

/*
	的のオブジェクト
*/
void TutorialStageSetterTarget::Set(Scene * Scene)
{
	// GameObjectのリストに追加->位置の設定
	Scene->AddGameObject<Billboard::Target>(LAYER_2D_EFFECT)->GetTransform().SetPosition(0.0f, 10.0f, 150.0f);
	for (int32_t i = 1; i < 3; ++i)
	{
		Scene->AddGameObject<Billboard::Target>(LAYER_2D_EFFECT)->GetTransform().SetPosition(40.0f * i, 5.0f, 100.0f);
		Scene->AddGameObject<Billboard::Target>(LAYER_2D_EFFECT)->GetTransform().SetPosition(-40.0f * i, 5.0f, 100.0f);
		Scene->AddGameObject<Billboard::Target>(LAYER_2D_EFFECT)->GetTransform().SetPosition(40.0f * i, 25.0f, 200.0f);
		Scene->AddGameObject<Billboard::Target>(LAYER_2D_EFFECT)->GetTransform().SetPosition(-40.0f * i, 25.0f, 200.0f);
	}
}

void TutorialStageSetterSupply::Set(Scene * Scene)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(30.0f, 0.0f, -100.0f);
	D3DXVECTOR3 scl = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, -0.2f, 0.0f);

	Scene->AddGameObject<Supply>(LAYER_3D_STAGE)->GetTransform().Set(pos, scl, rot);
}
