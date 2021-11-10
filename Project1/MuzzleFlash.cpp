/*--------------------------------------------------------------

	[MuzzleFlash.cpp]
	Author : �o���đ�

	�}�Y���t���b�V���̃G�t�F�N�g

---------------------------------------------------------------*/
#include "MuzzleFlash.h"
#include "Engine.h"
#include "Graphics.h"
#include "Application.h"
#include "Resource.h"
#include "GameCamera.h"
#include "Pause.h"

MuzzleFlash::MuzzleFlash()
{
	m_Transform = Actor::AddComponent<Transform>();
}

MuzzleFlash::~MuzzleFlash()
{
}

void MuzzleFlash::Begin()
{
	m_Transform->Begin();
}

void MuzzleFlash::Update()
{
	auto pause = Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->GetEnable();
	if (pause) { return; }
	Effect::Update();
	// �t���[������16�ɂȂ��������
	if (Effect::GetFrame() >= 16)
	{
		OnDestroy();
	}
}

void MuzzleFlash::Event()
{
}

void MuzzleFlash::Draw()
{
	// �e�N�X�`�����W���v�Z
	float x = Effect::GetFrame() % 4 * (1.0f / 4.0f);
	float y = Effect::GetFrame() / 4 * (1.0f / 4.0f);

	// map&unmap
	Effect::MapAndUnmap(x, y);

	// �}�g���N�X�̐ݒ�
	auto camera = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	DirectX::XMMATRIX view = camera->GetInverseView(); // View�̋t�s��

	DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(m_Transform->scale().x, m_Transform->scale().y, m_Transform->scale().z);
	DirectX::XMMATRIX trans = DirectX::XMMatrixTranslation(m_Transform->position().x, m_Transform->position().y, m_Transform->position().z);
	DirectX::XMMATRIX world = scale * view * trans;
	m_Graphics.SetWorldMatrix(world);

	// �e�N�X�`���̐ݒ�
	m_Resource.SetTexture(0, "Explosion");
	
	Effect::Draw();
}
