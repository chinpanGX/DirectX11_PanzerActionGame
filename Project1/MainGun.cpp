/*-----------------------------------------------------------

	[MainGun.cpp]
	Author : o‡ãÄ‘¾

	íÔ‚Ìå–C

------------------------------------------------------------*/
#include "Graphics.h"
#include "Resource.h"
#include "MainGun.h"

MainGun::MainGun(const std::string & Tag) : Parts(Tag)
{
	m_Transform = AddComponent<Transform>();
}

MainGun::~MainGun()
{
}

void MainGun::Begin()
{
	m_Transform->Begin();
}

void MainGun::Update()
{
	
}

void MainGun::Event()
{
}

void MainGun::Draw()
{
	Actor::UpdateMatrix(*m_Transform);
	GetGraphics().SetWorldMatrix(m_WorldMatrix);
	GetResource().SetStaticModel(Parts::GetTag() + "Gun");
}

void MainGun::UpdateMatrix(const D3DXMATRIX & ParentMatirx)
{
	D3DXMATRIX rot, trans;
	Math::Matrix::MatrixRotationRollPitchYaw(&rot, m_Transform->GetRotation());
	Math::Matrix::MatrixTranslation(&trans, m_Transform->GetPosition());
	auto local = rot * trans;
	m_WorldMatrix = local * ParentMatirx;
}