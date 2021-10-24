/*------------------------------------------------------------

	[Wall.h]
	Author : èoçá„ƒëæ

--------------------------------------------------------------*/
#pragma once
#include "StageObject.h"

class Wall final : public StageObject
{
public:
	Wall();
	~Wall();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};