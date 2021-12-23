/*-----------------------------------------------------------

	[TankBody.cpp]
	Author : èoçá„ƒëæ

------------------------------------------------------------*/
#include "Graphics.h"
#include "Resource.h"
#include "Body.h"


Body::Body(const std::string & Tag) : Parts(Tag)
{
	m_Transform = AddComponent<Transform>();
}

Body::~Body()
{
}

void Body::Begin()
{
	m_Transform->scale(1.3f);
}

void Body::Update()
{
	
}

void Body::Event()
{
}

void Body::Draw()
{
	Actor::UpdateMatrix(*m_Transform);
	graphics().SetWorldMatrix(m_WorldMatrix);
	resource().SetStaticModel(Parts::tag() + "Body");
}

void Body::UpdateMatrix(const D3DXMATRIX & ParentMatirx)
{
	D3DXMATRIX scale, rot, trans;
	Math::Matrix::MatrixScaling(&scale, m_Transform->scale());
	Math::Matrix::MatrixRotationRollPitchYaw(&rot, m_Transform->rotation());
	Math::Matrix::MatrixTranslation(&trans, m_Transform->position());
	auto local = scale * rot * trans;
	m_WorldMatrix = local;
}