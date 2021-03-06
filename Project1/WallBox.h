/*--------------------------------------------------------------

	[WallFence.h]
	Author : 出合翔太

	BOX型の壁

---------------------------------------------------------------*/
#pragma once
#include "StageObject.h"
#include <array>

namespace 
{
	// 法線ベクトルの方向を示す
	const int g_UnitX = 1;
	const int g_NegUnitX = 2;
	const int g_UnitZ = 3;
	const int g_NegUnitZ = 4;
}

class WallBox final : public StageObject
{
public:
	WallBox();
	~WallBox();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void Set(const D3DXVECTOR3& Pos, const D3DXVECTOR3& Size, int Normal = 10);

	// めり込んだ距離を返す
	D3DXVECTOR3 OffsetLength(const class OBB3& Obj);

private:
	// 平面をつくる
	void CreatePlane(int Normal);
	
	D3DXVECTOR3 m_PlanePoint;	// 平面の位置
	D3DXVECTOR3 m_Normal;		// 法線
	class GameCamera* m_Camera;
};

