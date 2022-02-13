/*--------------------------------------------------------------
	
	[AudioManager.h]
	Author : �o���đ�

	�I�[�f�B�I�Ǘ��N���X

----------------------------------------------------------------*/
#pragma once
#include "Manager.h"

// �Q�[��BGM
class GameAudio final : public IManager
{
public:
	GameAudio();
	~GameAudio();
	void Begin()override;
	void Update(GameManager* Manager, Pawn* Pawn, int32_t Type)override;
};

// ���U���gBGM
class ResultAudio final : public IManager
{
public:
	ResultAudio();
	~ResultAudio();
	void Begin()override;
	void Update(GameManager* Manager, Pawn* Pawn, int32_t Type)override;
	void Begin(bool IsPlayerWin);
};