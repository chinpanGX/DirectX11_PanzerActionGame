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
#include "Pivot.h"
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
	auto pause = Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->GetEnable();
	if (pause) { return; }
	auto& panzer = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->vehicle();
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
	// �J�����̏����擾
	auto camera = Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	D3DXMATRIX view = camera->view();

	// �r���[�̋t�s��
	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, nullptr, &view);//�t�s��
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;

	// ��Ԃ̏����擾
	auto& pilot = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->pivot();
	// ��Ԃ̈ʒu�ɃG�t�F�N�g�̈ʒu�����킹��
	m_Transform->position().x = pilot.transform().position().x;
	m_Transform->position().z = pilot.transform().position().z;

	// ���W�ϊ�
	D3DXMATRIX scale, rot, trans;
	Math::Matrix::MatrixScaling(&scale, m_Transform->scale());
	Math::Matrix::MatrixRotationRollPitchYaw(&rot, m_Transform->rotation());
	Math::Matrix::MatrixTranslation(&trans, m_Transform->position());
	D3DXMATRIX world = scale * rot * invView * trans;
	m_Graphics.SetWorldMatrix(world);
	
	// �}�e���A��
	Material m;
	m.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Graphics.SetMaterial(m);

	// �e�N�X�`���̐ݒ�
	m_Resource.SetTexture(0, "Reload");

	Effect::Draw();
}
