/*-------------------------------------------------------------

	[Resource.cpp]
	Author : �o���đ�

	�A�Z�b�g�̃v�[�����s��

--------------------------------------------------------------*/
#include "Resource.h"
#include "Graphics.h"
#include "Utility.h"


Resource::Resource(Graphics & Graphics) : m_Graphics(Graphics)
{
	// �e�탊�\�[�X���Ǘ����Ă���I�u�W�F�N�g
	m_Audio = std::make_unique<Audio>();
	m_Texture = std::make_unique<Texture>();
	m_VertexShader = std::make_unique <VertexShader>(m_Graphics);
	m_PixelShader = std::make_unique<PixelShader>(m_Graphics);
	m_StaticModel = std::make_unique<Prefabs::ModelPool>(m_Graphics);
}

Resource::~Resource()
{
	// �e�N�X�`��
	m_Texture->Unload("Bg");
	m_Texture->Unload("Ui");
	m_Texture->Unload("Grass");
	m_Texture->Unload("Billboard::Explosion");
	m_Texture->Unload("Reload");
	m_Texture->Unload("Gage");
	m_Texture->Unload("Effect");
	m_Texture->Unload("Number");
	m_Texture->Unload("Timer");
	m_Texture->Unload("ToonAnim");
	// ���f��
	m_StaticModel->Unload("Sky");
	m_StaticModel->Unload("Fence");
	m_StaticModel->Unload("Bullet");
	m_StaticModel->Unload("WallFence");
}

void Resource::LoadTexture(const std::string & Tag, const std::string & FileName)
{
	m_Texture->Load(Tag, FileName);
}

void Resource::UnloadTexture(const std::string & Tag)
{
	m_Texture->Unload(Tag);
}

#pragma region ���ʂŎg�����\�[�X�̃��[�h
void Resource::LoadTexture_ThreadA()
{
	m_Texture->Load("Bg", "Bg.png");
	m_Texture->Load("Ui", "Ui01.png");
	m_Texture->Load("Grass", "grass.dds");
	m_Texture->Load("Billboard::Explosion", "explosion.png");
	m_Texture->Load("Reload", "BulletIcon.png");
}

void Resource::LoadTexture_ThreadB()
{
	m_Texture->Load("Gage", "Gage.dds");
	m_Texture->Load("Effect", "Effect.jpg");
	m_Texture->Load("Number", "Number.png");
	m_Texture->Load("Timer", "TimeMarker.png");
	m_Texture->Load("ToonAnim", "SkillToon.dds");
}

void Resource::LoadModel_ThreadA()
{
	m_StaticModel->Load("Sky", "Sky.obj");
	m_StaticModel->Load("Fence", "Fence.obj");
	m_StaticModel->Load("Bullet", "TankBullet.obj");
	m_StaticModel->Load("WallFence", "Box.obj");
}
#pragma endregion ���ʂŎg�����\�[�X�̃��[�h

// ���f���̃��[�h�����E�A�����[�h����
void Resource::LoadModel(const std::string & Tag, const std::string & FileName)
{
	m_StaticModel->Load(Tag, FileName);
}

void Resource::UnloadModel(const std::string & Tag)
{
	m_StaticModel->Unload(Tag);
}

// �I�[�f�B�I�̃��[�h�E�A�����[�h
void Resource::AudioLoad(const std::string & Tag, bool Loop)
{
	m_Audio->Load(Tag, Loop);
}

void Resource::AudioUnload()
{
	m_Audio->Unload();
}

#pragma region �I�[�f�B�I�̑���
// �Đ�
void Resource::AudioPlay(const std::string & Tag, float Volume)
{
	m_Audio->Play(Tag, Volume);
}

// �X�g�b�v
void Resource::AudioStop()
{
	m_Audio->Stop();
}

// ���ʂ̕ύX
void Resource::AudioSetVolume(const std::string & Tag, float Volume)
{
	m_Audio->SetVolume(Tag, Volume);
}
#pragma endregion �I�[�f�B�I�֌W

// �e�N�X�`���̃Z�b�g
void Resource::SetTexture(int slot, const std::string & Tag)
{
	ID3D11ShaderResourceView* Transform = m_Texture->GetTexture(Tag);
	m_Graphics.GetDeviceContext()->PSSetShaderResources(slot, 1, &Transform);
}

#pragma region �V�F�[�_�[�̃Z�b�g
// �܂Ƃ߂ăZ�b�g����
void Resource::SetShader(const std::string & Tag)
{
	SetVertexShader(Tag);
	SetInputLayout(Tag);
	SetPixelShader(Tag);
}

// ���_�V�F�[�_�[
void Resource::SetVertexShader(const std::string& Tag)
{
	m_Graphics.GetDeviceContext()->VSSetShader(m_VertexShader->GetVertexShader(Tag), nullptr, 0);
}

// ���_���C�A�E�g
void Resource::SetInputLayout(const std::string& Tag)
{
	m_Graphics.GetDeviceContext()->IASetInputLayout(m_VertexShader->GetInputLayout(Tag));
}

// �s�N�Z���V�F�[�_�[
void Resource::SetPixelShader(const std::string& Tag)
{
	m_Graphics.GetDeviceContext()->PSSetShader(m_PixelShader->GetPixelShader(Tag), nullptr, 0);
}
#pragma endregion �V�F�[�_�[�̃Z�b�g

// ���f���̃Z�b�g
void Resource::SetStaticModel(const std::string& Tag)
{
	m_StaticModel->Draw(Tag);
