/*--------------------------------------------------------------

	[Reload.cpp]
	Author : �o���đ�

	�����[�h���ɕ`�悷��UI

--------------------------------------------------------------*/
#include "Reload.h"
#include "Engine.h"
#include "Graphics.h"
#include "Application.h"
#include "Resource.h"
#include "GameCamera.h"
#include "Panzer.h"
#include "Vehicle.h"
#include "Player.h"
#include "PanzerPilot.h"
#include "Pause.h"

Reload::Reload() : Effect()
{
	m_Transform = Actor::AddComponent<Transform>();
}

Reload::~Reload()
{
}

void Reload::Begin()
{
	m_Transform->Begin();
}

void Reload::Update()
{
	auto pause = Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->GetEnable();
	if (pause) { return; }
	auto& panzer = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->GetVehicle();
	m_Transform->rotation().z += 0.05f;
	if (panzer.GetStatus().GetFinishReload() == true)
	{
		OnDestroy();
	}
}

void Reload::Event()
{
}

void Reload::Draw()
{
	// �}�g���N�X�̐ݒ�
	auto camera = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	DirectX::XMMATRIX view = camera->GetInverseView(); // View�̋t�s��
	auto& pilot = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->GetPilot();
	m_Transform->position().x = pilot.GetTransform().position().x;
	m_Transform->position().z = pilot.GetTransform().position().z;
	DirectX::XMMATRIX scale = Math::Matrix::MatrixScaling(m_Transform->scale());
	DirectX::XMMATRIX rot = Math::Matrix::MatrixRotationQuatrnionRollPitchYaw(m_Transform->rotation());
	DirectX::XMMATRIX trans = Math::Matrix::MatrixTranslation(m_Transform->position());
	DirectX::XMMATRIX world = scale * rot * view * trans;
	m_Graphics.SetWorldMatrix(world);

	// �}�e���A��
	Material m;
	m.Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Graphics.SetMaterial(m);

	// �e�N�X�`���̐ݒ�
	m_Resource.SetTexture(0, "Reload");

	Effect::Draw();
}
