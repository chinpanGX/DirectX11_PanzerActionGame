/*------------------------------------------------------------
	
	[Grass.h]
	Author : o‡ãÄ‘¾

	‘‚Ì1ŒÂ‚Ìİ’è

-------------------------------------------------------------*/
#pragma once
#include "StageObject.h"

class Grass final : public StageObject
{
public:
	Grass();
	~Grass();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};

