/*--------------------------------------------------------------

	[TutorialStageSetter.cpp]
	Author : 出合翔太

	チュートリアルステージのオブジェクトを設置する

---------------------------------------------------------------*/
#include "Scene.h"
#include "WallBox.h"
#include "Target.h"
#include "TutorialStageSetter.h"

/*
	BOX型の壁
 */
void TutorialStageSetterWall::Set(Scene * scene)
{
	// サイズの設定
	D3DXVECTOR3 size = D3DXVECTOR3(3.0f, 3.0f, 3.0f);

	// GameObjectのリストに追加
	scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), size);
	scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(0.0f, 0.0f, -80.0f), size);
	scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(0.0f, 0.0f, -200.0f), size);
	for (int32_t i = 1; i < 20; ++i)
	{
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(12.0f * i, 0.0f, 0.0f), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(-12.0f * i, 0.0f, 0.0f), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(12.0f * i, 0.0f, -120.0f), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(-12.0f * i, 0.0f, -120.0f), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(150.0f, 0.0f, -12.0f * i), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(-150.0f, 0.0f, -12.0f * i), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(12.0f * i, 0.0f, -200.0f), size);
		scene->AddGameObject<WallBox>(LAYER_3D_STAGE)->Set(D3DXVECTOR3(-12.0f * i, 0.0f, -200.0f), size);
	}
}

/*
	的のオブジェクト
*/
void TutorialStageSetterTarget::Set(Scene * scene)
{
	// GameObjectのリストに追加->位置の設定
	scene->AddGameObject<Target>(LAYER_2D_EFFECT)->transform().position(0.0f, 10.0f, 150.0f);
	for (int32_t i = 1; i < 3; ++i)
	{
		scene->AddGameObject<Target>(LAYER_2D_EFFECT)->transform().position(40.0f * i, 5.0f, 100.0f);
		scene->AddGameObject<Target>(LAYER_2D_EFFECT)->transform().position(-40.0f * i, 5.0f, 100.0f);
		scene->AddGameObject<Target>(LAYER_2D_EFFECT)->transform().position(40.0f * i, 25.0f, 200.0f);
		scene->AddGameObject<Target>(LAYER_2D_EFFECT)->transform().position(-40.0f * i, 25.0f, 200.0f);
	}
}
