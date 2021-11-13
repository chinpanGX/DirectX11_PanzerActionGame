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

// ロード処理(name = ファイル名, loop = ループするかどうか)
void Audio::Load(const std::string & name, bool loop)
{
	m_Map[name] = std::make_unique<LoadAudio>();
	std::string file = "Asset\\Audio\\" + name + ".wav";
	m_Map[name]->Load(file, loop, m_xAudio2);
}

// 指定のものだけアンロード
void Audio::Unload(const std::string & name)
{
	m_Map[name]->Unload();
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

void Audio::Play(const std::string & name, float volume)
{
	// 再生するオーディオを探す
	auto itr = m_Map.find(name);
	// キーが見つかったら再生
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
	// 再生するオーディオを探す
	auto itr = m_Map.find(name);
	// キーが見つかったら再生
	if (itr != m_Map.end())
	{
		itr->second->SetVolume(volume);
	}
}
