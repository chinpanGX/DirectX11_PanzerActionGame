/*--------------------------------------------------------------
	
	[Manager.h]
	Author : 出合翔太

	管理クラス

----------------------------------------------------------------*/
#pragma once
#include <stdint.h>
#include <memory>
#include <string>

class GameManager;
class Pawn;
class IManager
{
public:
	virtual ~IManager() {};
	virtual void Update(GameManager* manager, Pawn* pawn, int32_t Type) = 0;
};

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