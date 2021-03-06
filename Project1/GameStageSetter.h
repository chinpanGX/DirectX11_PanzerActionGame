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
	void Set(Scene* Scene)override;
};

// BOX^ÌÇ
class GameStageSetterWallBox final : public ISetterObject
{
public:
	void Set(Scene* Scene)override;
};

// ân_
class GameStageSetterSupply final : public ISetterObject
{
public:
	void Set(Scene* Scene)override;
};

// â
class GameStageSetterRock final : public ISetterObject
{
public:
	void Set(Scene* Scene)override;
private:
	void SetBackGround(); // wipÌâ
	void Set(float x, float y, float z, float size);
	std::vector<D3DXVECTOR3> m_Position;
	std::vector<D3DXVECTOR3> m_Size;
	Scene* m_Scene;
	int32_t m_ObjectCount = 0;
};