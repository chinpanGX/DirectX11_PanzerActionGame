/*--------------------------------------------------------------
	
	[ResultState.h]
	Author : 出合翔太

	リザルトのカラー変更のステートを管理

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
		if (m_TimeCounter > 60) // カウントが60になったら、α値を加算する
		{
			m_Alpha += 0.1f;
			if (m_Alpha > 0.7f)
			{
				m_Alpha = 0.7f;
			}
		}
	}

	void SetEnter()
	{
		m_Enter = true;
	}

	const bool GetEnter() const
	{
		return m_Enter;
	}

	void SelectTop()
	{
		m_Select--;
		if (m_Select < 0)
		{
			m_Select = 0;
		}
	}
	void SelectDown()
	{
		m_Select++;
		if (m_Select > 2)
		{
			m_Select = 2;
		}
	}
	const int32_t GetSelect() const
	{
		return m_Select;
	}
	const float GetAlpha() const
	{
		return m_Alpha;
	}
private:
	int32_t m_TimeCounter; // 時間経過
	float m_Alpha; // 描画透明度
	int32_t m_Select;
	bool m_Enter = false;
};

