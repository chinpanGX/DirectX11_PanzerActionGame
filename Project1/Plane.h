/*------------------------------------------------------------

	[Plane.h]
	Author : 出合翔太

	床オブジェクト

--------------------------------------------------------------*/
#pragma once
#include "StageObject.h"

class Plane final : public StageObject
{
public:
	Plane();
	~Plane();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:	
	std::unique_ptr<class Renderer3D> m_Renderer;
};

