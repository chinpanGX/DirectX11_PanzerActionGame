/*-----------------------------------------------------------
	
	[State.h]
	Author : �o���đ�

	�e�X�e�[�g�̊��N���X

------------------------------------------------------------*/
#pragma once
#include "stdafx.h"

// �e�X�e�[�g�̊��N���X
class StateBase
{
public:
	StateBase() : m_Frame(30) {}
	inline StateBase(const int32_t& Frame) : m_Frame(Frame), m_FrameZeroFlag(false){}
	~StateBase() = default;
protected:
	inline void OnFrameZero()
	{
		m_FrameZeroFlag = true;
	}
	// �t���[�����̃J�E���g�_�E��
	inline void FrameCountDown()
	{
		// �t���[�������f�N�������g���ăt���[�������O�ɂȂ�����t���O��true�ɂ��Ēʒm����
		m_Frame--;
		if (m_Frame <= 0)
		{
			OnFrameZero();
		}
	}

	// Getter
	inline const int32_t& GetFrame()const { return m_Frame; }
	inline const bool& GetFrameZeroFlag() const { return m_FrameZeroFlag; }
private:
	int32_t m_Frame;
	bool m_FrameZeroFlag; // �t���[�������O�ɂȂ�����true
};

// �e�̃X�e�[�g
class BulletState : public StateBase
{
public:
	inline BulletState() : StateBase(256) {}
	inline virtual ~BulletState() {}
	virtual void Update(class Bullet* Bullet, float DeltaTime) = 0;
};

