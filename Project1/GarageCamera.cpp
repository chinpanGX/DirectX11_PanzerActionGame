/*-----------------------------------------------------------

	[GarageCamera.cpp]
	Author : o‡ãÄ‘¾

	íÔ‘qŒÉ‚ÌƒJƒƒ‰

------------------------------------------------------------*/
#include "GarageCamera.h"
#include "Input.h"

GarageCamera::GarageCamera()
{
	m_Transform = Actor::AddComponent<Transform>();
	m_Target = Math::Vector3(-43.3f, 3.0f, 74.8f);
}

GarageCamera::~GarageCamera()
{
}

void GarageCamera::Begin()
{
	m_Transform->position(Math::Vector3(15.2f, 5.5f, 2.3f));
}

void GarageCamera::Update()
{
	
}

void GarageCamera::Event()
{
}

void GarageCamera::Draw()
{
	SetViewMatrix();
	SetProjectionMatrix();
}
