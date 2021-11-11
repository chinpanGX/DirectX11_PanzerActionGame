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

SkillParticle::SkillParticle() : Effect()
{
	m_Transform = Actor::AddComponent<Transform>();
	m_Transform->scale(10.0f);
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
	auto pause = Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->GetEnable();
	if (pause) { return; }

	Effect::Update();

	// �t���[������16�ɂȂ��������
	if (Effect::GetFrame() >= 16)
	{
		OnDestroy();
	}
}

void SkillParticle::Event()
{
}

void SkillParticle::Draw()
{
	// �e�N�X�`�����W���v�Z
	float x = Effect::GetFrame() % 2 * (1.0f / 2.0f);
	float y = Effect::GetFrame() / 8 * (1.0f / 8.0f);

	// map&unmap
	Effect::MapAndUnmap(x, y);

	// �}�g���N�X�̐ݒ�
		// �}�g���N�X�̐ݒ�
	// �J�����̏����擾����
	auto camera = Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	DirectX::XMFLOAT4X4 tmp = camera->view();
	DirectX::XMMATRIX view = DirectX::XMLoadFloat4x4(&tmp);

	// View�̋t�s��
	DirectX::XMMATRIX inverseViewMatrix = DirectX::XMMatrixIdentity();
	inverseViewMatrix = DirectX::XMMatrixInverse(nullptr, inverseViewMatrix);
	inverseViewMatrix.r[3].m128_f32[0] = 0.0f;
	inverseViewMatrix.r[3].m128_f32[1] = 0.0f;
	inverseViewMatrix.r[3].m128_f32[2] = 0.0f;

	// ���W�ϊ�
	DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(m_Transform->scale().x, m_Transform->scale().y, m_Transform->scale().z);
	DirectX::XMMATRIX trans = DirectX::XMMatrixTranslation(m_Transform->position().x, m_Transform->position().y, m_Transform->position().z);
	DirectX::XMMATRIX world = scale * inverseViewMatrix * trans;
	m_Graphics.SetWorldMatrix(world);

	// �}�e���A��
	Material m;
	m.Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Graphics.SetMaterial(m);

	// �e�N�X�`���̐ݒ�
	m_Resource.SetTexture(0, "SkillEffect");

	Effect::Draw();
}