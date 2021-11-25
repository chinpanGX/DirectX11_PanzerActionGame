/*------------------------------------------------------------

	[Cpu.h]
	�v���C���[�����삵�Ȃ��I�u�W�F�N�g
	Author : �o���đ�	

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

