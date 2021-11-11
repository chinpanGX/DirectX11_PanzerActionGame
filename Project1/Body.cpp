/*-----------------------------------------------------------

	[TankBody.cpp]
	Author : èoçá„ƒëæ

------------------------------------------------------------*/
#include "Graphics.h"
#include "Resource.h"
#include "Body.h"


Body::Body(const std::string & Tag) : Parts(Tag)
{
	m_Transform = Actor::AddComponent<Transform>();
}

Body::~Body()
{
}

void Body::Begin()
{
	m_Transform->position(Math::Vector3::Zero);
	m_Transform->rotation(Math::Quaternion::Identity);
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
	auto m = DirectX::XMLoadFloat4x4(&m_WorldMatrix);
	graphics().SetWorldMatrix(m);
	resource().SetStaticModel(Parts::GetTag() + "Body");
}

void Body::UpdateMatrix(const DirectX::XMFLOAT4X4 & ParentMatirx)
{
	DirectX::XMMATRIX scale, rot, trans;
	scale = Math::Matrix::MatrixScaling(m_Transform->scale());
	rot = Math::Matrix::MatrixRotationQuatrnionRollPitchYaw(m_Transform->rotation());
	trans = Math::Matrix::MatrixTranslation(m_Transform->position());
	auto local = scale * rot * trans;
	DirectX::XMStoreFloat4x4(&m_WorldMatrix, local);
}