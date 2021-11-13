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
	auto pause = Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->GetEnable();
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
	// �J�����̏����擾����
// �}�g���N�X�̐ݒ�
	auto camera = Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	D3DXMATRIX view = camera->view();

	// �r���[�̋t�s��
	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view);//�t�s��
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;

	// ���W�ϊ�
	D3DXMATRIX world, scale, rot, trans;
	Math::Matrix::MatrixScaling(&scale, transform().scale());
	Math::Matrix::MatrixTranslation(&trans, transform().position());
	world = scale * invView * trans;
	m_Graphics.SetWorldMatrix(world);

	// �e�N�X�`���̐ݒ�
	m_Resource.SetTexture(0, "Explosion");
	
	Effect::Draw();
}
