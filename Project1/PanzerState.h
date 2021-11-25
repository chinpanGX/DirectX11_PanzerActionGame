/*--------------------------------------------------------------
	
	[PanzerState.h]
	Author ; �o���đ�

	��ԃX�e�[�g�̊��N���X

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



