/*--------------------------------------------------------------

	[SkillParticle.cpp]
	�X�L���p�̃p�[�e�B�N��
	Author : �o���đ�

---------------------------------------------------------------*/
#include "Engine.h"
#include "Graphics.h"
#include "Resource.h"
#include "Application.h"
#include "GameCamera.h"
#include "Pause.h"
#include "SkillParticle.h"
#include "Fps.h"

SkillParticle::SkillParticle() : Effect()
{
	m_Transform = AddComponent<Transform>();
	m_Transform->SetScale(10.0f);
	m_Time = 0.0;
}

SkillParticle::~SkillParticle()
{
}

void SkillParticle::Begin()
{
	
}

void SkillParticle::Update()
{
	// �|�[�Y�����ǂ���
	if(Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE)->NowPausing()) { return; }
	

	Effect::Update();
}

void SkillParticle::Event()
{
}

void SkillParticle::Draw()
{
	// �e�N�X�`�����W���v�Z
	float x = Effect::GetFrame() % 4 * (1.0f / 4.0f);
	float y = Effect::GetFrame() / 4 * (1.0f / 4.0f);

	// map&unmap
	Effect::MapAndUnmap(x, y);

	// �}�g���N�X�̐ݒ�
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

	// �}�e���A��
	Material m;
	m.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Graphics.SetMaterial(m);

	// �e�N�X�`���̐ݒ�
	m_Resource.SetTexture(0, "SkillEffect");

	Effect::Draw();
}