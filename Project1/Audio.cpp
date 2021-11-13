/*-----------------------------------------------------------

	[Audio.h]
	Author : �o���đ�

------------------------------------------------------------*/
#include "myLib.h"
#include "Audio.h"
#include "Graphics.h"
#include "Utility.h"

Audio::Audio()
{
	HRESULT hr;
	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&m_xAudio2, 0);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "Xaudio2�I�u�W�F�N�g�쐬���s");

		// COM���C�u�����̏I������
		CoUninitialize();

		return;
	}

	// �}�X�^�[�{�C�X�̐���
	hr = m_xAudio2->CreateMasteringVoice(&m_masteringVoice);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "�}�X�^�[�{�C�X�̐����Ɏ��s");
		if (m_xAudio2)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			m_xAudio2->Release();
			m_xAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return;
	}
}

Audio::~Audio()
{
	Unload();
	// �}�X�^�[�{�C�X�̔j��
	m_masteringVoice->DestroyVoice();
	m_masteringVoice = NULL;

	if (m_xAudio2)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		m_xAudio2->Release();
		m_xAudio2 = NULL;
	}

	// COM���C�u�����̏I������
	CoUninitialize();
}

// ���[�h����(name = �t�@�C����, loop = ���[�v���邩�ǂ���)
void Audio::Load(const std::string & name, bool loop)
{
	m_Map[name] = std::make_unique<LoadAudio>();
	std::string file = "Asset\\Audio\\" + name + ".wav";
	m_Map[name]->Load(file, loop, m_xAudio2);
}

// �w��̂��̂����A�����[�h
void Audio::Unload(const std::string & name)
{
	m_Map[name]->Unload();
}

// ���ׂăA�����[�h
void Audio::Unload()
{
	// �I�[�f�B�I�̃A�����[�h
	for (auto itr = m_Map.begin(); itr != m_Map.end(); ++itr)
	{
		itr->second->Unload();
		itr->second.reset();
		itr->second = nullptr;
	}
	// �N���A
	m_Map.clear();
	if (!m_Map.empty())
	{
		throw std::domain_error("m_Map is Not empty");
	}
}

void Audio::Play(const std::string & name, float volume)
{
	// �Đ�����I�[�f�B�I��T��
	auto itr = m_Map.find(name);
	// �L�[������������Đ�
	if (itr != m_Map.end())
	{
		itr->second->SetVolume(volume);
		itr->second->Play();
	}
	else
	{
		throw std::domain_error("Not find key");
	}
}

void Audio::Stop()
{
	for (auto itr = m_Map.begin(); itr != m_Map.end(); ++itr)
	{
		itr->second->Stop();
	}
}

void Audio::SetVolume(const std::string & name, float volume)
{
	// �Đ�����I�[�f�B�I��T��
	auto itr = m_Map.find(name);
	// �L�[������������Đ�
	if (itr != m_Map.end())
	{
		itr->second->SetVolume(volume);
	}
}
