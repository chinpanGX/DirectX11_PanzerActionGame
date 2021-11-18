/*------------------------------------------------------------
	
	[PlaneGarage.h]
	Author : o‡ãÄ‘¾

	íÔ‘qŒÉ‚Ì’n–Ê

-------------------------------------------------------------*/
#pragma once
#include "StageObject.h"

class PlaneGarage final : public StageObject
{
public:
	PlaneGarage();
	~PlaneGarage();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:
	std::unique_ptr<class Renderer3D> m_Renderer;
};

