/*--------------------------------------------------------------

	[WallFence.h]
	Author : �o���đ�

	BOX�^�̕�

---------------------------------------------------------------*/
#pragma once
#include "StageObject.h"
#include <array>

namespace 
{
	// �@���x�N�g���̕���������
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

	// �߂荞�񂾋�����Ԃ�
	D3DXVECTOR3 OffsetLength(const class OBB3& obj);

private:
	void CreatePlane(int Normal);
	D3DXVECTOR3 m_PlanePoint;
	D3DXVECTOR3 m_Normal;
};

