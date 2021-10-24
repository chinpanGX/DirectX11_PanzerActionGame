/*--------------------------------------------------------------
	
	[AudioManager.h]
	Author : 出合翔太

	オーディオ管理クラス

----------------------------------------------------------------*/
#pragma once
#include "Manager.h"

// ゲームBGM
class GameAudio final : public IManager
{
public:
	GameAudio();
	~GameAudio();
	void Update(GameManager* manager, Pawn* pawn, int32_t Type)override;
};

// リザルトBGM
class ResultAudio final : public IManager
{
public:
	ResultAudio();
	~ResultAudio();
	void Update(GameManager* manager, Pawn* pawn, int32_t Type)override;
	void Begin(bool IsPlayerWin);
};