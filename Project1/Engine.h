/*------------------------------------------------------------
	
	[Engine.h]
	Author : 出合翔太

-------------------------------------------------------------*/
#pragma once
#include "Singleton.h"
#include "myLib.h"
#include <Windows.h>

class Graphics;
class Resource;
class Application;
class Engine final : public Singleton<Engine>
{
	friend Singleton<Engine>;
public:
	void Init(HINSTANCE h);
	void Run();
	const Math::Vector2 GetWindowSize() const;
	const float GetWidth() const;
	const float GetHeight() const;
	const HWND& GetHwnd() const;
	const std::shared_ptr<Graphics> GetGraphics() const;
	const std::shared_ptr<Resource> GetResource() const;
	const std::shared_ptr<Application> GetApplication() const;
protected:
	Engine();
	~Engine();
private:
	void CreateGameWindow(HWND& hwnd, WNDCLASSEX& window);
	WNDCLASSEX m_WindowClass;
	HWND m_hwnd;
	
	std::shared_ptr<Graphics> m_Graphics;		// DirectX11
	std::shared_ptr<Resource> m_Resource;		// リソース管理
	std::shared_ptr<Application> m_Application;	// アプリケーション
	// Windowモード/FullScreenモード
	bool m_WindowMode;

	// サイズ
	const float m_Width = 1920.0f;
	const float m_Height = 1080.0f;
};

