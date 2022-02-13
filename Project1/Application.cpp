/*------------------------------------------------------------

	[Application.cpp]
	Author : �o���đ�

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

Application::Application(Graphics & Graphics) : m_Graphics(Graphics), m_Fade(nullptr), m_Scene(nullptr)
{
	m_Fade = std::make_unique<Fade>(*this, *Engine::Get().GetResource(), Fps::Get());
	
	PanzerNameList::Get().Register(); // ��Ԃ̖��O��o�^
	
	// �V�[���̃Z�b�g
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
	// �Q�[��
	m_Scene->Update();
	m_Fade->Update();
}

void Application::Draw()
{
	m_Graphics.Begin();

	// �Q�[��
	m_Scene->Draw();
	m_Fade->Draw();

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
