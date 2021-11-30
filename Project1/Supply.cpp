/*-------------------------------------------------------------

	[Supply.cpp]
	Author : o‡ãÄ‘¾

	•â‹‹’n“_

--------------------------------------------------------------*/
#include "Resource.h"
#include "Supply.h"

Supply::Supply()
{
	m_Transform = AddComponent<Transform>();
	m_Collider = AddComponent<Collider>();
}

Supply::~Supply()
{
}

void Supply::Begin()
{	
	auto size = D3DXVECTOR3(5.0f, 1.0, 5.0f);
	m_Collider->SetSphere3(*m_Transform, 5.0f * 2.0f);
	m_Collider->SetOBB3(*m_Transform, size * 2.0f);
}

void Supply::Update()
{
}

void Supply::Event()
{
}

void Supply::Draw()
{
	resource().SetShader("Default");
	UpdateMatrix(*m_Transform);
	resource().SetStaticModel("Supply");
	//m_Collider->SystemDraw();
}
