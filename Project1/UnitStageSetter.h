/*--------------------------------------------------------------

	[UintStageSetter.h]
	Author : 出合翔太

	各ステージに共通オブジェクトを設置する

---------------------------------------------------------------*/
#pragma once
#include "ISetterObject.h"

class Scene;

// スカイドーム
class StageSetterSkydome final : public ISetterObject
{
public:
	void Set(Scene* Scene);
};

// 地面
class StageSetterPlane final : public ISetterObject
{
public:
	void Set(Scene* Scene);
};

class StageSetterGameWorld final : public ISetterObject
{
public:
	void Set(Scene* Scene);
};