/*-----------------------------------------------------------
	
	[Bullet.h]
	Author : �o���đ�

-------------------------------------------------------------*/
#pragma once
#include "Actor.h"

class Bullet : public Actor
{
public:
	inline Bullet() : m_FrameZeroFlag(false) 
	{

	}
	inline ~Bullet() 
	{
		m_FrameZeroFlag = false;
	}
	inline void Begin()override {}
	inline void Update()override {}
	inline void Event()override {}
	inline void Draw()override {}

	// �e�̐���
	virtual void Create(const D3DXVECTOR3& Position, const D3DXVECTOR3& Vector) = 0;
	virtual void ChangeState(std::unique_ptr<class BulletState> State) = 0;
	virtual void OnCollision() = 0;

	// �t���[���J�E���g�_�E��
	inline void FrameCountDown()
	{
		m_Frame--;
		if (m_Frame <= 0) // �O�ɂȂ�����ʒm����
		{
			m_FrameZeroFlag = true;
		}
	}
	
	// D3DXVECTOR3�̕��@�x�N�g��
	inline const D3DXVECTOR3& GetDirectionVector() const
	{
		return m_DirectionVector;
	}

	// �З͌���
	inline void DownDDE()
	{
		m_Distdecay -= 0.02f; // ������
		if (m_Distdecay < 0.7f)
		{
			m_Distdecay = 0.7f;
		}
	}

	inline float GetDDE()
	{
		return m_Distdecay;
	}

	// ���x
	inline const float GetSpeed() const
	{
		return m_Speed;
	}

	inline const bool& GetFrameZeroFlag() const
	{
		return m_FrameZeroFlag;
	}
protected:
	// �v���p�e�B�̐ݒ� (Vector = ���ł��������x�N�g��, Frame = �t���[����)
	inline void SetProperty(const D3DXVECTOR3& Vector, const float& Speed = 10.0f, const uint32_t& Frame = 60)
	{
		m_DirectionVector = Vector;
		m_Speed = Speed;
		m_Frame = Frame;
	}
private:
	D3DXVECTOR3 m_DirectionVector;	// ���ł�������
	uint32_t m_Frame;			// �t���[����
	float m_Speed;				// ���x
	float m_Distdecay = 1.2f;	// �����ɂ��З͌���
	bool m_FrameZeroFlag;		// �t���[�������O�ɂȂ�����true�ɂ��Ēʒm����
};

