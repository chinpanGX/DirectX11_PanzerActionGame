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

Billboard::MuzzleFlash::MuzzleFlash()
{
	m_Transform = AddComponent<Transform>();
}

Billboard::MuzzleFlash::~MuzzleFlash()
{
}

void Billboard::MuzzleFlash::Begin()
{
	m_Transform->Begin();
}

void Billboard::MuzzleFlash::Update()
{
	if(Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE)->NowPausing()) { return; }
	
	Effect::Update();
	// �t���[������16�ɂȂ��������
	if (Effect::GetFrame() >= 16)
	{
		OnDestroy();
	}
}

void Billboard::MuzzleFlash::Event()
{
}

void Billboard::MuzzleFlash::Draw()
{
	// �e�N�X�`�����W���v�Z
	float x = Effect::GetFrame() % 4 * (1.0f / 4.0f);
	float y = Effect::GetFrame() / 4 * (1.0f / 4.0f);

	// map&unmap
	Effect::MapAndUnmap(x, y);

	// �}�g���N�X�̐ݒ�
	// �J�����̏����擾����
	auto camera = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	D3DXMATRIX view = camera->GetView();

	// �r���[�̋t�s��
	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view);//�t�s��
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;

	// ���W�ϊ�
	D3DXMATRIX world, scale, rot, trans;
	Math::Matrix::MatrixScaling(&scale, GetTransform().GetScale());
	Math::Matrix::MatrixTranslation(&trans, GetTransform().GetPosition());
	world = scale * invView * trans;
	m_Graphics.SetWorldMatrix(world);

	// �e�N�X�`���̐ݒ�
	m_Resource.SetTexture(0, "Billboard::Explosion");
	
	Effect::Draw();
}
