/*-----------------------------------------------------------

	[GarageCamera.h]
	Author : o‡ãÄ‘¾

	íÔ‘qŒÉ‚ÌƒJƒƒ‰

------------------------------------------------------------*/
#pragma once
#include "Camera.h"

class GarageCamera final : public Camera
{
public:
	GarageCamera();
	~GarageCamera();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};

