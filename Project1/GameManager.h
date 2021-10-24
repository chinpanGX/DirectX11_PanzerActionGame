/*--------------------------------------------------------------

	[GameManager.h]
	Author : 出合翔太

	ゲームの進行を管理

	リスポーン, 殲滅ゲージ, 勝敗

---------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include "Manager.h"
#include <memory>
#include <array>

enum ID : int32_t
{
	E_Player,
	//E_CPU1,
	E_Enemy1,
	//E_Enemy2,
};

class GameManager final : public DefaultObject
{
public:
	GameManager();
	~GameManager();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;

	// イベント開始
	void BeginEvent(class Pawn* pawn, int32_t Id);
	
	// ゲーム終了
	void GameSet();
	const bool GetGameEnd()const;

	// どちらが勝ったか
	void SetWinner(int32_t type);
private:
	// trueでゲーム終了
	bool m_GameEnd = false;
	std::array<std::unique_ptr<IManager>, 3> m_Manager;
};

// リザルト
class ResultManager final : public DefaultObject
{
public:
	ResultManager();
	~ResultManager(){}
	void Begin()override;
	void Update()override {}
	void Event()override {}
	void Draw()override {}
};