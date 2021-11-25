/*--------------------------------------------------------------
	
	[PanzerState.h]
	Author ; 出合翔太

	戦車ステートの基底クラス

---------------------------------------------------------------*/
#pragma once
#include "State.h"
#include "myLib.h"

class Cpu;
class Pivot;
class AIController;
class PanzerState : public StateBase
{
public:
	PanzerState() {}
	virtual ~PanzerState() {}
	virtual void Update(Cpu* pCpu, float deltaTime) = 0;
};



