/*-----------------------------------------------------------

	[Fps.cpp]
	Author : o‡ãÄ‘¾

-------------------------------------------------------------*/
#include "Fps.h"

void Fps::Init()
{
	m_isReset = false;
	deltaTime = 0.0f;
	m_dwExcLastTime = 0;
	m_dwCurrentTime = 0;
	m_dwOldCurrentTime = 0;
	m_Framerate = 60.0f;

	timeBeginPeriod(1);
	m_dwExcLastTime = timeGetTime();
}

void Fps::Uninit()
{
	timeEndPeriod(1);
}

bool Fps::Update()
{
	m_dwOldCurrentTime = m_dwCurrentTime;
	m_dwCurrentTime = timeGetTime();
	if (m_dwCurrentTime - m_dwExcLastTime >= (1000 / m_Framerate))
	{
		deltaTime = (m_dwCurrentTime - m_dwExcLastTime) / 1000.0f;
		if (deltaTime >= 1 / m_Framerate)
		{
			deltaTime = 1 / m_Framerate;
		}
		if (m_isReset == true)
		{
			deltaTime = 0;
			m_isReset = false;
		}
		m_dwExcLastTime = m_dwCurrentTime;
		return true;

	}
	else
	{
		return false;
	}
}

void Fps::Reset()
{
	m_isReset = true;
}

Fps::Fps()
{

}

Fps::~Fps()
{
}
