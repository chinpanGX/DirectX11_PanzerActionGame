/*------------------------------------------------------------

	[Application.cpp]
	Author : 出合翔太

-------------------------------------------------------------*/
#include "Graphics.h"
#include "Resource.h"
#include "Engine.h"
#include "Fps.h"
#include "Fade.h"
#include "Scene.h"
#include "TitleScene.h"
#include "PanzerNameList.h"
#include "Application.h"
#include <time.h>

Application::Application(Graphics & graphics) : m_Graphics(graphics), m_Fade(nullptr), m_Scene(nullptr)
{
	m_Fade = std::make_unique<Fade>(*this, *Engine::Get().resource(), Fps::Get());
	
	PanzerNameList::Get().Register(); // 戦車の名前を登録
	
	// シーンのセット
	SetScene<GameScene::Title>();
	m_Fade->SetState(m_Fade->E_IN);
	ChangeScene(m_Fade->GetNextScene());
}

Application::~Application()
{
	m_Scene->Uninit();
	delete m_Scene;
}

void Application::Init()
{
	
}

void Application::Update()
{
	// ゲーム
	m_Scene->Update();
	m_Fade->Update();
}

void Application::Draw()
{
	m_Graphics.Begin();
	// ライトの設定
	Light light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f);
	light.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Graphics.SetLight(light);

	// ゲーム
	m_Scene->Draw();
	m_Fade->Draw();

	light.Enable = false;
	m_Graphics.SetLight(light);
	
	m_Graphics.End();
}

Scene* Application::GetScene() const
{
	if (m_Scene)
	{
		return m_Scene;
	}
	return nullptr;
}

void Application::ChangeScene(Scene * scene)
{
	if (m_Scene)
	{
		m_Scene->Uninit();
		delete m_Scene;
	}
	m_Scene = scene;
	scene->Init();
}
