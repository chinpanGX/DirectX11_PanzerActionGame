/*--------------------------------------------------------------
	
	[PanzerState.h]
	Author ; 出合翔太

	戦車ステートの基底クラス

---------------------------------------------------------------*/
#pragma once
#include "State.h"
#include "myLib.h"

class Enemy;
class Pivot;
class AIController;
class PanzerState : public StateBase
{
public:
	PanzerState() {}
	virtual ~PanzerState() {}
	virtual void Begin(class Player* pPlayer) = 0;
	virtual void Update(Enemy* pEnemy, float deltaTime) = 0;
};