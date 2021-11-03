/*--------------------------------------------------------------

	[WallFence.cpp]
	Author : 出合翔太

	トレーニング用の壁

---------------------------------------------------------------*/
#include "Resource.h"
#include "WallBox.h"

WallBox::WallBox()
{
	m_Transform = Actor::AddComponent<Transform>();
	m_BoxComponent = Actor::AddComponent<BoxComponent>();
}

WallBox::~WallBox()
{
}

void WallBox::Begin()
{
	m_BoxComponent->SetOBB3(*m_Transform, m_Transform->GetScale());
	m_BoxComponent->SetAABB3(*m_Transform, m_Transform->GetScale());
}

void WallBox::Update()
{
	Actor::UpdateCollision(*m_BoxComponent);
}

void WallBox::Event()
{
}

void WallBox::Draw()
{
	GetResource().SetShader("Default");
	UpdateMatrix(*m_Transform);
	GetResource().SetStaticModel("WallFence");
}
