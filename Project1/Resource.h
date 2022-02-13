/*------------------------------------------------------------
	
	[Resoruce.h]
	Author : �o���đ�

	���\�[�X���Ǘ�

-------------------------------------------------------------*/
#pragma once
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Audio.h"

class Graphics;
class Resource final
{
public:
	Resource() = delete;
	Resource(Graphics& Graphics);
	~Resource();

	// �e�N�X�`���̃��[�h
	void LoadTexture(const std::string& Tag, const std::string& FileName);
	void UnloadTexture(const std::string& Tag);

	// ���ʂŎg�����\�[�X�̃��[�h�E�A�����[�h
	void LoadTexture_ThreadA();
	void LoadTexture_ThreadB();	
	void LoadModel_ThreadA();
	void Unload();
	
	// ���f���̃��[�h
	void LoadModel(const std::string& Tag, const std::string& FileName);
	void UnloadModel(const std::string& Tag);

	//�@�I�[�f�B�I
	void AudioLoad(const std::string& Tag, bool Loop);
	void AudioUnload();	// �A�����[�h

	// �I�[�f�B�I�̑���
	void AudioPlay(const std::string& Tag, float Volume = 1.0f);
	void AudioStop();
	void AudioSetVolume(const std::string& Tag, float Volume);

	// �e�N�X�`��
	void SetTexture(int slot, const std::string& Tag); // slot = �ݒ肷��X���b�g�AID = �i�[ID

	// �V�F�[�_�[���܂Ƃ߂Đݒ肷��
	void SetShader(const std::string& Tag);

	// ���_�V�F�[�_�[
	void SetVertexShader(const std::string& Tag);
	void SetInputLayout(const std::string& Tag);
	// �s�N�Z���V�F�[�_�[
	void SetPixelShader(const std::string& Tag);

	// ���f��
	void SetStaticModel(const std::string& Tag);

private:
	Graphics& m_Graphics;
	std::unique_ptr<Audio> m_Audio;
	std::unique_ptr<Texture> m_Texture;
	std::unique_ptr<VertexShader> m_VertexShader;
	std::unique_ptr<PixelShader> m_PixelShader;
	std::unique_ptr<Prefabs::ModelPool> m_StaticModel;
};


