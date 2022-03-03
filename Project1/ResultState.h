/*--------------------------------------------------------------
	
	[ResultState.h]
	Author : �o���đ�

	���U���g�̃J���[�ύX�̃X�e�[�g���Ǘ�

----------------------------------------------------------------*/
#pragma once
#include<stdint.h>

class ResultState
{
public:
	ResultState() : m_Select(0), m_TimeCounter(0), m_Alpha(0.0f) { }
	~ResultState() {}
	void Update()
	{
		m_TimeCounter++;
		if (m_TimeCounter > 60) // �J�E���g��60�ɂȂ�����A���l�����Z����
		{
			m_Alpha += 0.1f;
			if (m_Alpha > 0.7f)
			{
				m_Alpha = 0.7f;
			}
		}
	}

	// ���肵�����ǂ���
	void SetEnter()
	{
		m_Enter = true;
	}

	const bool GetEnter() const
	{
		return m_Enter;
	}

	// ��̑I��
	void SelectTop()
	{
		m_Select--;
		if (m_Select < 0)
		{
			m_Select = 0;
		}
	}

	// ���̑I��
	void SelectDown()
	{
		m_Select++;
		if (m_Select > 2)
		{
			m_Select = 2;
		}
	}

	// �I�����Ă�����̂�Ԃ�
	const int32_t GetSelect() const
	{
		return m_Select;
	}

	// ���l
	const float GetAlpha() const
	{
		return m_Alpha;
	}
private:
	int32_t m_TimeCounter; // ���Ԍo��
	float m_Alpha; // �`�擧���x
	int32_t m_Select;
	bool m_Enter = false;
};

