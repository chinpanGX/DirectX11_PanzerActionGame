/*------------------------------------------------------------
	
	[Engine.h]
	Author : �o���đ�

-------------------------------------------------------------*/
#pragma once
#include "Singleton.h"
#include "myLib.h"
#include <Windows.h>

#define SCREEN_WIDTH	(1920)
#define SCREEN_HEIGHT	(1080)

class Graphics;
class Resource;
class Application;
class Engine final : public Singleton<Engine>
{
	friend Singleton<Engine>;
public:
	void Init(HINSTANCE h);
	void Run();

	const HWND& GetHwnd() const;
	const std::shared_ptr<Graphics> graphics() const;
	const std::shared_ptr<Resource> resource() const;
	const std::shared_ptr<Application> application() const;
protected:
	Engine();
	~Engine();
private:
	void CreateGameWindow(HWND& hwnd, WNDCLASSEX& window);
	WNDCLASSEX m_WindowClass;
	HWND m_hwnd;
	
	std::shared_ptr<Graphics> m_Graphics;		// DirectX11
	std::shared_ptr<Resource> m_Resource;		// ���\�[�X�Ǘ�
	std::shared_ptr<Application> m_Application;	// �A�v���P�[�V����
	
	// �E�B���h�E���[�h��L���ɂ��邩
	bool m_EnableWindowMode;
};

