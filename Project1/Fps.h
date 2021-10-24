/*-----------------------------------------------------------

	[Fps.h]
	Author : èoçá„ƒëæ

-------------------------------------------------------------*/
#pragma once
#include <Windows.h>
#include "Singleton.h"
#include <stdint.h>

class Fps final : public Singleton<Fps>
{
	friend Singleton<Fps>;
public:
	void Init();
	void Uninit();
	bool Update();
	void Reset();

	float deltaTime;
protected:
	Fps();
	~Fps();
private:
	DWORD m_dwExcLastTime;
	DWORD m_dwCurrentTime;
	DWORD m_dwOldCurrentTime;
	float m_Framerate;
	bool m_isReset;
};
