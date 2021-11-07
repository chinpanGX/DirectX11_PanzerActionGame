/*-----------------------------------------------------------

	[Explosion.cpp]
	Author : �o���đ�

	�����G�t�F�N�g

------------------------------------------------------------*/
#include "Explosion.h"
#include "Engine.h"
#include "Graphics.h"
#include "Application.h"
#include "Resource.h"
#include "GameCamera.h"
#include "Pause.h"

Explosion::Explosion() : Effect()
{
	m_Transform = Actor::AddComponent<Transform>();
}

Explosion::~Explosion()
{
}

void Explosion::Begin()
{
	m_Transform->SetScale(3.0f, 3.0f, 0.0f);
}

void Explosion::Update()
{
	// �|�[�Y�����ǂ���
	auto pause = Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->GetEnable();
	if (pause) { return; }

	Effect::Update();
	// �t���[������16�ɂȂ��������
	if (Effect::GetFrame() >= 16)
	{
		OnDestroy();
	}
}

void Explosion::Event()
{
}

void Explosion::Draw()
{	
	// �e�N�X�`�����W���v�Z
	float x = Effect::GetFrame() % 4 * (1.0f / 4.0f);
	float y = Effect::GetFrame() / 4 * (1.0f / 4.0f);
	
	// map&unmap
	Effect::MapAndUnmap(x, y);
	
	// �}�g���N�X�̐ݒ�
	auto camera = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	DirectX::XMMATRIX view = camera->GetInverseView(); // View�̋t�s��
	
	DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(m_Transform->GetScale().x, m_Transform->GetScale().y, m_Transform->GetScale().z);	
	DirectX::XMMATRIX trans = DirectX::XMMatrixTranslation(m_Transform->GetPosition().x, m_Transform->GetPosition().y, m_Transform->GetPosition().z);
	DirectX::XMMATRIX world = scale * view * trans;
	m_Graphics.SetWorldMatrix(world);

	// �}�e���A��
	Material m;
	m.Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Graphics.SetMaterial(m);

	// �e�N�X�`���̐ݒ�
	m_Resource.SetTexture(0, "Explosion");
	
	Effect::Draw();
}