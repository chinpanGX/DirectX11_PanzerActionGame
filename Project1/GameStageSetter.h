/*--------------------------------------------------------------
	
	[GameStageSetter.h]
	Author : oãÄ¾

	Q[Xe[WÌIuWFNgðÝu·é

---------------------------------------------------------------*/
#pragma once
#include "ISetterObject.h"

class Scene;
// ò
class GameStageSetterFence final : public ISetterObject
{
public:
	void Set(Scene* scene)override;
};

// BOX^ÌÇ
class GameStageSetterWallBox final : public ISetterObject
{
public:
	void Set(Scene* scene)override;
};

// ân_
class GameStageSetterSupply final : public ISetterObject
{
public:
	void Set(Scene* scene)override;
};

// â
class GameStageSetterRock final : public ISetterObject
{
public:
	void Set(Scene* scene)override;
};