/*--------------------------------------------------------------

	[TutorialStageSetter.h]
	Author : 出合翔太

	チュートリアルステージのオブジェクトを設置する

---------------------------------------------------------------*/
#pragma once
#include "ISetterObject.h"

class Scene;

// 壁の設置
class TutorialStageSetterWall final : public ISetterObject
{
public:
	void Set(Scene* Scene)override;
};

// 的の設置
class TutorialStageSetterTarget final : public ISetterObject
{
public:
	void Set(Scene* Scene)override;
};

class TutorialStageSetterSupply final : public ISetterObject
{
public:
	void Set(Scene* Scene)override;
};