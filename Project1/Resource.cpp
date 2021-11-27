/*-------------------------------------------------------------

	[Resource.cpp]
	Author : �o���đ�

	�A�Z�b�g�̃v�[�����s��

--------------------------------------------------------------*/
#include "Resource.h"
#include "Graphics.h"
#include "Utility.h"


Resource::Resource(Graphics & graphics) : m_Graphics(graphics)
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
	m_Texture->Unload("Bg");
	m_Texture->Unload("Ui");
	m_Texture->Unload("Grass");
	m_Texture->Unload("Explosion");
	m_Texture->Unload("Reload");
	m_Texture->Unload("Gage");
	m_Texture->Unload("Effect");
	m_Texture->Unload("Number");
	m_Texture->Unload("Timer");
	m_Texture->Unload("Toon");
	m_Texture->Unload("ToonAnim");
	m_StaticModel->Unload("Sky");
	m_StaticModel->Unload("Fence");
	m_StaticModel->Unload("Bullet");
	m_StaticModel->Unload("WallFence");
}

void Resource::LoadTexture(const std::string & tag, const std::string & filename)
{
	m_Texture->Load(tag, filename);
}

void Resource::UnloadTexture(const std::string & tag)
{
	m_Texture->Unload(tag);
}

#pragma region ���ʂŎg�����\�[�X�̃��[�h
void Resource::LoadTexture_ThreadA()
{
	m_Texture->Load("Bg", "Bg.png");
	m_Texture->Load("Ui", "Ui01.png");
	m_Texture->Load("Grass", "grass.jpg");
	m_Texture->Load("Explosion", "explosion.png");
	m_Texture->Load("Reload", "Reload.png");
}

void Resource::LoadTexture_ThreadB()
{
	m_Texture->Load("Gage", "Gage.png");
	m_Texture->Load("Effect", "Effect.jpg");
	m_Texture->Load("Number", "Number.png");
	m_Texture->Load("Timer", "TimeMarker.png");
	m_Texture->Load("Toon", "Toon1.png");
	m_Texture->Load("ToonAnim", "SkillToon.png");
}

void Resource::LoadModel_ThreadA()
{
	m_StaticModel->Load("Sky", "Other\\Sky.obj");
	m_StaticModel->Load("Fence", "Other\\Fence.obj");
	m_StaticModel->Load("Bullet", "Other\\TankBullet.obj");
	m_StaticModel->Load("WallFence", "Other\\Box.obj");
}
#pragma endregion ���ʂŎg�����\�[�X�̃��[�h

void Resource::LoadModel(const std::string & tag, const std::string & filename)
{
	m_StaticModel->Load(tag, filename);
}

void Resource::UnloadModel(const std::string & tag)
{
	m_StaticModel->Unload(tag);
}
#pragma endregion ���f���̃��[�h

#pragma region AudioSystem
void Resource::AudioLoad(const std::string & tag, bool loop)
{
	m_Audio->Load(tag, loop);
}

void Resource::AudioUnload()
{
	m_Audio->Unload();
}

// �I�[�f�B�I�̑���
void Resource::AudioPlay(const std::string & tag, float volume)
{
	m_Audio->Play(tag, volume);
}

void Resource::AudioStop()
{
	m_Audio->Stop();
}

void Resource::AudioSetVolume(const std::string & tag, float volume)
{
	m_Audio->SetVolume(tag, volume);
}
#pragma endregion �I�[�f�B�I�֌W

void Resource::SetTexture(int slot, const std::string & Tag)
{
	ID3D11ShaderResourceView* t = m_Texture->GetTexture(Tag);
	m_Graphics.GetDeviceContext()->PSSetShaderResources(slot, 1, &t);
}

void Resource::SetShader(const std::string & Tag)
{
	SetVertexShader(Tag);
	SetInputLayout(Tag);
	SetPixelShader(Tag);
}

void Resource::SetVertexShader(const std::string& Tag)
{
	m_Graphics.GetDeviceContext()->VSSetShader(m_VertexShader->GetVertexShader(Tag), nullptr, 0);
}

void Resource::SetInputLayout(const std::string& Tag)
{
	m_Graphics.GetDeviceContext()->IASetInputLayout(m_VertexShader->GetInputLayout(Tag));
}

void Resource::SetPixelShader(const std::string& Tag)
{
	m_Graphics.GetDeviceContext()->PSSetShader(m_PixelShader->GetPixelShader(Tag), nullptr, 0);
}

void Resource::SetStaticModel(const std::string& Tag)
{
	m_StaticModel->Draw(Tag);
}
