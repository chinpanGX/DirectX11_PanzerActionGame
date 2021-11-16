/*--------------------------------------------------------------
	
	[Timer.h]
	Author : �o���đ�

	�Q�[���̐������Ԃ�\������@�u�������Ԃ͂T���v

---------------------------------------------------------------*/
#pragma once
#include "IDrawNumber.h"
#include "DefaultObject.h"

// ��
class DrawTimerMinute final : public IDrawNumber
{
public:
	DrawTimerMinute();
	~DrawTimerMinute();
	void Draw(int32_t n)override;
};

// �b
class DrawTimerSecond final : public IDrawNumber
{
public:
	DrawTimerSecond();
	~DrawTimerSecond();
	void Draw(int32_t n)override;
};

namespace GameBg
{
	class Timer final : public Bg
	{
	public:
		Timer();
		~Timer();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
	private:
		std::array<std::unique_ptr<IDrawNumber>, 2> m_DrawTimer;
		const float m_TimeLimit_min; // �^�C�����~�b�g�i���j
		int32_t m_Minute; // ��
		int32_t m_Second;	  // �b
		float m_NowTime;  // ���̎���
		// �ݒ�ς݂��ǂ����̃t���O
		bool m_Is1minSetColor = false;
		bool m_Is10secSetColor = false;
	};
}
