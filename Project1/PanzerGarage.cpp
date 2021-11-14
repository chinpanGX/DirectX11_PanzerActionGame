/*------------------------------------------------------------

	[PanzerGarage.cpp]
	Author : 出合翔太

	戦車倉庫

-------------------------------------------------------------*/
#include "Engine.h"
#include "Resource.h"
#include "Graphics.h"
#include "Application.h"
#include "PanzerGarage.h"

PanzerGarage::PanzerGarage() : m_Graphics(*Engine::Get().graphics())
{
	m_Transform = Actor::AddComponent<Transform>();
}

PanzerGarage::~PanzerGarage()
{
}

void PanzerGarage::Begin()
{
	m_Transform->position(0.0f, 0.0f, -6.0f);
	m_Transform->scale(3.0f);
	//// ライトの設定
	//Light light;
	//light.Enable = true;
	//light.Direction = D3DXVECTOR4(10.0f, 10.0f, -20.0f, 0.0f);
	//D3DXVec4Normalize(&light.Direction, &light.Direction);
	//light.Position = D3DXVECTOR4(100.0f, 0.0f, 0.0f, 1.0f);
	//light.Angle = D3DXVECTOR4(Math::Pi / 180.0f * 2.0f, 1.0f, 1.0f, 1.0f);
	//m_Graphics.SetLight(light);
}

void PanzerGarage::Update()
{
	
}

void PanzerGarage::Event()
{
}

void PanzerGarage::Draw()
{
	// ライトの設定
	Light light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(0.0f, 1.0f, -1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Position = D3DXVECTOR4(10.0f, 50.0f, 20.0f, 1.0f);
	light.Angle = D3DXVECTOR4(1.0f, 1.0f, Math::Pi / 180.0f * 5.0f, 1.0f);
	m_Graphics.SetLight(light);
	//resource().SetShader("Default");
	resource().SetShader("PixelLighting");
	UpdateMatrix(*m_Transform);
	resource().SetStaticModel("PanzerGarage");

	light.Enable = false;
	m_Graphics.SetLight(light);
}
