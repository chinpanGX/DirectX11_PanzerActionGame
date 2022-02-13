/*-----------------------------------------------------------

	[Audio.h]
	Author : 出合翔太

------------------------------------------------------------*/
#include "myLib.h"
#include "Audio.h"
#include "Graphics.h"
#include "Utility.h"

Audio::Audio()
{
	HRESULT hr;
	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&m_xAudio2, 0);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "Xaudio2オブジェクト作成失敗");

		// COMライブラリの終了処理
		CoUninitialize();

		return;
	}

	// マスターボイスの生成
	hr = m_xAudio2->CreateMasteringVoice(&m_masteringVoice);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "マスターボイスの生成に失敗");
		if (m_xAudio2)
		{
			// XAudio2オブジェクトの開放
			m_xAudio2->Release();
			m_xAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return;
	}
}

Audio::~Audio()
{
	Unload();
	// マスターボイスの破棄
	m_masteringVoice->DestroyVoice();
	m_masteringVoice = NULL;

	if (m_xAudio2)
	{
		// XAudio2オブジェクトの開放
		m_xAudio2->Release();
		m_xAudio2 = NULL;
	}

	// COMライブラリの終了処理
	CoUninitialize();
}

// ロード処理(Name = ファイル名, loop = ループするかどうか)
void Audio::Load(const std::string & Name, bool Loop)
{
	m_Map[Name] = std::make_unique<LoadAudio>();
	std::string file = "Asset\\Audio\\" + Name + ".wav";
	m_Map[Name]->Load(file, Loop, m_xAudio2);
}

// 指定のものだけアンロード
void Audio::Unload(const std::string & Name)
{
	m_Map[Name]->Unload();
}

// すべてアンロード
void Audio::Unload()
{
	// オーディオのアンロード
	for (auto itr = m_Map.begin(); itr != m_Map.end(); ++itr)
	{
		itr->second->Unload();
		itr->second.reset();
		itr->second = nullptr;
	}
	// クリア
	m_Map.clear();
	if (!m_Map.empty())
	{
		throw std::domain_error("m_Map is Not empty");
	}
}

void Audio::Play(const std::string & Name, float Volume)
{
	// 再生するオーディオを探す
	auto itr = m_Map.find(Name);
	// キーが見つかったら再生
	if (itr != m_Map.end())
	{
		itr->second->SetVolume(Volume);
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

void Audio::SetVolume(const std::string & Name, float Volume)
{
	// 再生するオーディオを探す
	auto itr = m_Map.find(Name);
	// キーが見つかったら再生
	if (itr != m_Map.end())
	{
		itr->second->SetVolume(Volume);
	}
}
