/*------------------------------------------------------------

	[Cpu.h]
	プレイヤーが操作しないオブジェクト
	Author : 出合翔太	

--------------------------------------------------------------*/
#pragma once
#include "Pawn.h"

class Cpu : public Pawn
{
public:
	Cpu();
	~Cpu();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	virtual void ChangeState(std::unique_ptr<class PanzerState> State) = 0;
	void UseSkill();
protected:
	std::unique_ptr<class PanzerState> m_State;
};

