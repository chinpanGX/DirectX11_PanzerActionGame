/*------------------------------------------------------------
	
	[Engine.cpp]
	Author : 出合翔太

-------------------------------------------------------------*/
#include "Input.h"
#include "Fps.h"
#include "Graphics.h"
#include "Application.h"
#include "Resource.h"
#include "Engine.h"
#include <thread>

#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

namespace
{
	void AsyncLoad()
	{
		auto sleepTime = std::chrono::seconds(4);
		std::this_thread::sleep_for(sleepTime);
	}
}

// ウィンドウプロシージャ
LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Engine::Init(HINSTANCE h)
{
	auto result = CoInitializeEx(0, COINITBASE_MULTITHREADED);
	//MessageBox(NULL, "ウィンドウモードで起動しますか？", "画面モード確認", MB_YESNO) == IDYES ? m_EnableWindowMode = true : m_EnableWindowMode = false;
	m_EnableWindowMode = false;
	CreateGameWindow(m_hwnd, m_WindowClass);	// ゲームウィンドウ
	InputDevice::Init(h, m_hwnd, false);	// コントローラの初期
}

void Engine::Run()
{
	//_メモリリークの検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 使えるメモリ領域を示す
	//int32_t step = 10; //10MB
	//int32_t count = 0;
	//char temp[20];

	// 使えるスレッド数は12個
	//auto count = std::thread::hardware_concurrency()

	// ウィンドウ表示
	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);

	srand((unsigned int)time(NULL));


	// フレームレートの初期化
	Fps& fps = Fps::Get();
	fps.Init();

	// DirectX11 
	m_Graphics = std::make_shared<Graphics>();

	// リソース
	m_Resource = std::make_shared<Resource>(*m_Graphics);

	// モデルとテクスチャをマルチスレッドでロードする
	std::thread loadTexture_A(&Resource::LoadTexture_ThreadA, m_Resource);
	std::thread loadTexture_B(&Resource::LoadTexture_ThreadB, m_Resource);
	std::thread loadModel(&Resource::LoadModel_ThreadA, m_Resource);
	
	loadTexture_A.join();
	loadTexture_B.join();
	loadModel.join();

	// ゲームアプリケーション
	m_Application = std::make_shared<Application>(*m_Graphics);
	
	// メッセージループ
	MSG msg;
	while (true)
	{
	
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) // PostQuitMessage()が呼ばれたらループ終了
			{
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (fps.Update())
			{
				InputDevice::Update(); // コントローラの更新
				m_Application->Update();
				m_Application->Draw();
			}
		}
	}

	// 2070MB
	//wsprintf(temp, "Total %d MB\n", count * step);
	//MessageBox(NULL, temp, "TEST", MB_OK);

	m_Application.reset();
	m_Resource.reset();
	m_Graphics.reset();
	fps.Uninit();
	InputDevice::Uninit();  // コントローラの終了処理 
	timeEndPeriod(1);		// 分解能を戻す
	UnregisterClass(m_WindowClass.lpszClassName, m_WindowClass.hInstance); // ウィンドウクラスの登録を解除
}

const HWND & Engine::GetHwnd() const
{
	return m_hwnd;
}

const std::shared_ptr<class Graphics> Engine::GetGraphics() const
{
	return m_Graphics;
}

const std::shared_ptr<class Resource> Engine::GetResource() const
{
	return m_Resource;
}

const std::shared_ptr<class Application> Engine::GetApplication() const
{
	return m_Application;
}

Engine::Engine() : m_EnableWindowMode(true)
{
}

Engine::~Engine()
{
}

void Engine::CreateGameWindow(HWND & hwnd, WNDCLASSEX & window)
{
	if (m_EnableWindowMode == true) // ウィンドウモード
	{
		HINSTANCE hInstance = GetModuleHandle(NULL);
		// ウィンドウの生成＆登録
		window.cbSize = sizeof(WNDCLASSEX);
		window.lpfnWndProc = (WNDPROC)WndProc; // コールバック関数の指定
		window.lpszClassName = "Dx11";			// アプリケーション名
		window.hInstance = GetModuleHandle(0);	// ハンドルの指定
		RegisterClassEx(&window);				// アプリケーションクラス
		RECT wrc = { 0, 0, static_cast<LONG>(SCREEN_WIDTH), static_cast<LONG>(SCREEN_HEIGHT) };
		AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);
		// ウィンドウオブジェクトの生成
		hwnd = CreateWindow(window.lpszClassName,		// クラス名
			"ゲームアプリ",								// タイトルバー
			WS_OVERLAPPEDWINDOW,						// ウィンドウタイプ
			CW_USEDEFAULT, CW_USEDEFAULT,				// 表示xy座標はOSに任せる
			wrc.right - wrc.left, wrc.bottom - wrc.top, // ウィンドウ幅と高さ
			NULL, NULL, window.hInstance, NULL);		// ウィンドウハンドル, メニューハンドル,呼び出しアプリケーションハンドル, 追加パラメータ
	}
	else if (m_EnableWindowMode == false)
	{
		HINSTANCE hInstance = GetModuleHandle(NULL);
		// ウィンドウの生成＆登録
		window.cbSize = sizeof(WNDCLASSEX);
		window.lpfnWndProc = (WNDPROC)WndProc; // コールバック関数の指定
		window.lpszClassName = "Dx11";			// アプリケーション名
		window.hInstance = GetModuleHandle(0);	// ハンドルの指定
		RegisterClassEx(&window);				// アプリケーションクラス
		RECT wrc = { 0, 0, static_cast<LONG>(SCREEN_WIDTH), static_cast<LONG>(SCREEN_HEIGHT) };
		AdjustWindowRect(&wrc, WS_CAPTION, false);
		// ウィンドウオブジェクトの生成
		hwnd = CreateWindow(window.lpszClassName,		// クラス名
			"ゲームアプリ",								// タイトルバー
			WS_VISIBLE | WS_POPUP,						// ウィンドウタイプ
			CW_USEDEFAULT, CW_USEDEFAULT,				// 表示xy座標はOSに任せる
			wrc.right - wrc.left, wrc.bottom - wrc.top, // ウィンドウ幅と高さ
			NULL, NULL, window.hInstance, NULL);		// ウィンドウハンドル, メニューハンドル,呼び出しアプリケーションハンドル, 追加パラメータ
	}
}
