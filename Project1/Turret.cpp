/*-----------------------------------------------------------

	[Turret.cpp]
	Author : èoçá„ƒëæ

------------------------------------------------------------*/
#include "Graphics.h"
#include "Resource.h"
#include "Turret.h"

Turret::Turret(const std::string & Tag) : Parts(Tag)
{
	m_Transform = Actor::AddComponent<Transform>();
}

Turret::~Turret()
{
}

void Turret::Begin()
{
	m_Transform->position(Math::Vector3::Zero);
	m_Transform->rotation(Math::Quaternion::Identity);
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
	auto m = DirectX::XMLoadFloat4x4(&m_WorldMatrix);
	GetGraphics().SetWorldMatrix(m);
	GetResource().SetStaticModel(Parts::GetTag() + "Turret");
}

void Turret::UpdateMatrix(const DirectX::XMFLOAT4X4 & ParentMatirx)
{
	DirectX::XMMATRIX rot, trans;
	rot = Math::Matrix::MatrixRotationQuatrnionRollPitchYaw(m_Transform->rotation());
	trans = Math::Matrix::MatrixTranslation(m_Transform->position());
	auto local = rot * trans;
	auto m = local * DirectX::XMLoadFloat4x4(&ParentMatirx);
	DirectX::XMStoreFloat4x4(&m_WorldMatrix, m);
}
