/*--------------------------------------------------------------

	[GameStage.h]
	Author : o‡ãÄ‘¾

---------------------------------------------------------------*/
#pragma once
#include "Stage.h"

class GameStage final : public Stage
{
public:
	GameStage();
	~GameStage();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};

