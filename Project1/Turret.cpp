/*-----------------------------------------------------------

	[Turret.cpp]
	Author : èoçá„ƒëæ

------------------------------------------------------------*/
#include "Graphics.h"
#include "Resource.h"
#include "Turret.h"

Turret::Turret(const std::string & Tag) : Parts(Tag)
{
	m_Transform = AddComponent<Transform>();
}

Turret::~Turret()
{
}

void Turret::Begin()
{
	m_Transform->Begin();
}

void Turret::Update()
{

}

void Turret::Event()
{
}

void Turret::Draw()
{
	Actor::UpdateMatrix(*m_Transform);
	GetGraphics().SetWorldMatrix(m_WorldMatrix);
	GetResource().SetStaticModel(Parts::GetTag() + "Turret");
}

void Turret::UpdateMatrix(const D3DXMATRIX & ParentMatirx)
{
	D3DXMATRIX rot, trans;
	Math::Matrix::MatrixRotationRollPitchYaw(&rot, m_Transform->GetRotation());
	Math::Matrix::MatrixTranslation(&trans, m_Transform->GetPosition());
	auto local = rot * trans;
	m_WorldMatrix = local * ParentMatirx;
}
