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
	m_Transform->SetPosition(Math::Vector3::Zero);
	m_Transform->SetRotation(Math::Quaternion::Identity);
	m_Transform->SetScale(1.3f);
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
	GetGraphics().SetWorldMatrix(m);
	GetResource().SetStaticModel(Parts::GetTag() + "Body");
}

void Body::UpdateMatrix(const DirectX::XMFLOAT4X4 & ParentMatirx)
{
	DirectX::XMMATRIX scale, rot, trans;
	scale = Math::Matrix::MatrixScaling(m_Transform->GetScale());
	rot = Math::Matrix::MatrixRotationQuatrnionRollPitchYaw(m_Transform->GetRotation());
	trans = Math::Matrix::MatrixTranslation(m_Transform->GetPosition());
	auto local = scale * rot * trans;
	DirectX::XMStoreFloat4x4(&m_WorldMatrix, local);
}