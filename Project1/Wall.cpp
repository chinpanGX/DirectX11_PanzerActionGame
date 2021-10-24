/*------------------------------------------------------------
	
	[Wall.cpp]
	Author : èoçá„ƒëæ

-------------------------------------------------------------*/
#include "Graphics.h"
#include "Resource.h"
#include "Renderer3D.h"
#include "Wall.h"

Wall::Wall()
{
	m_Transform = Actor::AddComponent<Transform>();
}

Wall::~Wall()
{
}

void Wall::Begin()
{
	m_Transform->SetPosition(0.0f, 30.0f, 0.0f);
	m_Transform->SetScale(500.0f, 30.0f, 500.0f);
}

void Wall::Update()
{
}

void Wall::Event()
{
}

void Wall::Draw()
{
	//UpdateMatrix(*m_Transform);
	//m_Resource.SetStaticModel(Prefabs::StaticModelID::WALL);
}
