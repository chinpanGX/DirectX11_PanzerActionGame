/*--------------------------------------------------------------

	[TutorialStage.h]
	Author : 出合翔太

	チュートリアルステージ

---------------------------------------------------------------*/
#pragma once
#include "Stage.h"

// チュートリアル用のステージ
class TutorialStage : public Stage
{
public:
	TutorialStage();
	~TutorialStage();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};
