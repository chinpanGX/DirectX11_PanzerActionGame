/*--------------------------------------------------------------
	
	[Timer.h]
	Author : �o���đ�

	�Q�[���̐������Ԃ�\������@�u�������Ԃ͂T���v

---------------------------------------------------------------*/
#pragma once
#include "DrawNumber.h"
#include "DefaultObject.h"

// ��
class DrawTimerMinute final : public DrawNumber
{
public:
	DrawTimerMinute();
	~DrawTimerMinute();
	void Draw(int32_t value)override;
};

// �b
class DrawTimerSecond final : public DrawNumber
{
public:
	DrawTimerSecond();
	~DrawTimerSecond();
	void Draw(int32_t value)override;
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
		std::array<std::unique_ptr<DrawNumber>, 2> m_DrawTimer;
		const float m_TimeLimitMin; // �^�C�����~�b�g�i���j
		int32_t m_Minute; // ��
		int32_t m_Second;	  // �b
		float m_NowTime;  // ���̎���
		// �ݒ�ς݂��ǂ����̃t���O
		bool m_Is1minSetColor = false;
		bool m_Is10secSetColor = false;
	};
}
