/*--------------------------------------------------------------
	
	[GameStageSetter.h]
	Author : 出合翔太

	ゲームステージのオブジェクトを設置する

---------------------------------------------------------------*/
#pragma once
#include "ISetterObject.h"

class Scene;
// 柵
class GameStageSetterFence final : public ISetterObject
{
public:
	void Set(Scene* scene);
};

// BOX型に壁
class GameStageSetterWallBox final : public ISetterObject
{
public:
	void Set(Scene* scene);
};