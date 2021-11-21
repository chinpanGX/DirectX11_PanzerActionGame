/*--------------------------------------------------------------

	[WallFence.h]
	Author : èoçá„ƒëæ

	BOXå^ÇÃï«

---------------------------------------------------------------*/
#pragma once
#include "StageObject.h"

class WallBox final : public StageObject
{
public:
	WallBox();
	~WallBox();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void Set(D3DXVECTOR3 Pos, D3DXVECTOR3 Size = D3DXVECTOR3(5.0f, 5.0f, 5.0f));

private:
	void CreatePlane();
	D3DXPLANE m_Plane[4];
};

