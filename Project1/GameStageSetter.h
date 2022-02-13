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
	void Set(Scene* Scene)override;
};

// BOX型の壁
class GameStageSetterWallBox final : public ISetterObject
{
public:
	void Set(Scene* Scene)override;
};

// 補給地点
class GameStageSetterSupply final : public ISetterObject
{
public:
	void Set(Scene* Scene)override;
};

// 岩
class GameStageSetterRock final : public ISetterObject
{
public:
	void Set(Scene* Scene)override;
private:
	void SetBackGround(); // 背景用の岩
	void Set(float x, float y, float z, float size);
	std::vector<D3DXVECTOR3> m_Position;
	std::vector<D3DXVECTOR3> m_Size;
	Scene* m_Scene;
	int32_t m_ObjectCount = 0;
};