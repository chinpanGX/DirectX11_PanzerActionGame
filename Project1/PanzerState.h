/*--------------------------------------------------------------
	
	[PanzerState.h]
	Author ; 出合翔太

---------------------------------------------------------------*/
#pragma once
#include "State.h"
#include "myLib.h"

class Pawn;
class Pivot;
class AIController;
class PanzerState : public StateBase
{
public:
	PanzerState();
	virtual ~PanzerState() {}
	virtual void Update(Pawn* pPawn, float deltaTime) = 0;
protected:
	const float& SearchRange()const { return m_SearchRange; }
	const float& ShotRange()const { return m_ShotRange; }

	// プレイヤーの位置を取得する
	const D3DXVECTOR3& SearchPlayer() const;
private:
	const float m_SearchRange = 200.0f; // サーチ範囲
	const float m_ShotRange = 50.0f;	// 射程範囲
};



