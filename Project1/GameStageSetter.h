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
	void Set(Scene* scene)override;
};

// BOX型の壁
class GameStageSetterWallBox final : public ISetterObject
{
public:
	void Set(Scene* scene)override;
};

// 補給地点
class GameStageSetterSupply final : public ISetterObject
{
public:
	void Set(Scene* scene)override;
};

// 岩
class GameStageSetterRock final : public ISetterObject
{
public:
	void Set(Scene* scene)override;
};