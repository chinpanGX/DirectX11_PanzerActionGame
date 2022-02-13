/*------------------------------------------------------------

	[PanzerGarage.cpp]
	Author : 出合翔太

	戦車倉庫のオブジェクト

-------------------------------------------------------------*/
#include "Engine.h"
#include "Resource.h"
#include "Graphics.h"
#include "Application.h"
#include "PanzerGarage.h"

PanzerGarage::PanzerGarage() : m_Graphics(*Engine::Get().GetGraphics())
{
	m_Transform = AddComponent<Transform>();
}

PanzerGarage::~PanzerGarage()
{
}

void PanzerGarage::Begin()
{
	m_Transform->SetPosition(0.0f, 0.0f, -6.0f);
	m_Transform->SetScale(3.0f);
}

void PanzerGarage::Update()
{
	
}

void PanzerGarage::Event()
{
}

void PanzerGarage::Draw()
{
	GetResource().SetShader("PixelLighting");
	UpdateMatrix(*m_Transform);
	GetResource().SetStaticModel("PanzerGarage");
}
