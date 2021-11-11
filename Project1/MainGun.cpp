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
	m_Transform = Actor::AddComponent<Transform>();
}

MainGun::~MainGun()
{
}

void MainGun::Begin()
{
	m_Transform->position(Math::Vector3::Zero);
	m_Transform->rotation(Math::Quaternion::Identity);
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
	auto m = DirectX::XMLoadFloat4x4(&m_WorldMatrix);
	graphics().SetWorldMatrix(m);
	resource().SetStaticModel(Parts::GetTag() + "Gun");
}

void MainGun::UpdateMatrix(const DirectX::XMFLOAT4X4 & ParentMatirx)
{
	DirectX::XMMATRIX rot, trans;
	rot = Math::Matrix::MatrixRotationQuatrnionRollPitchYaw(m_Transform->rotation());
	trans = Math::Matrix::MatrixTranslation(m_Transform->position());
	auto local = rot * trans;
	auto m = local * DirectX::XMLoadFloat4x4(&ParentMatirx);
	DirectX::XMStoreFloat4x4(&m_WorldMatrix, m);
}