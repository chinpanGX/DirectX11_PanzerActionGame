/*--------------------------------------------------------------
	
	[Spwan.h]
	Author : 出合翔太

	スポーンをする

--------------------------------------------------------------*/
#pragma once
#include "Manager.h"
#include "myLib.h"
#include <vector>

// リスポーン
class ResPawn final : public IManager
{
public:
	ResPawn();
	~ResPawn();
	void Begin()override;
	void Update(GameManager* Manager, Pawn* Pawn, int32_t Type)override;
	const bool GetResPawn() const;
private:
	std::vector<std::unique_ptr<class ISPawn>> m_SPawn;
	bool m_IsResPawn = false; // trueでリスポーンする
};

class ISPawn
{
public:
	ISPawn() {}
	virtual ~ISPawn() {}
	virtual void SetSPawn() = 0;
};

// プレイヤーのスポーン
class PlayerSPawn final : public ISPawn
{
public:
	PlayerSPawn();
	~PlayerSPawn();
	void SetSPawn()override;
};

// エネミーのスポーン
class EnemySPawn final : public ISPawn
{
public:
	EnemySPawn();
	~EnemySPawn();
	 void SetSPawn()override;
};
