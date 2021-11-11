/*------------------------------------------------------------
	
	[Grass.cpp]
	Author : èoçá„ƒëæ

--------------------------------------------------------------*/
#include "Graphics.h"
#include "Resource.h"
#include "Grass.h"

Grass::Grass()
{
	m_Transform = AddComponent<Transform>();
}

Grass::~Grass()
{
}

void Grass::Begin()
{
	m_Transform->position(0.0f, 1.0f, 0.0f);
}

void Grass::Update()
{
}

void Grass::Event()
{
}

void Grass::Draw()
{
	resource().SetShader("Default");
	UpdateMatrix(*m_Transform);
	resource().SetStaticModel("Grass");
}
