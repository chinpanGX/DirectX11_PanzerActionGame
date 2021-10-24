/*-----------------------------------------------------------

	[Audio.h]
	Author : 出合翔太

------------------------------------------------------------*/
#include "myLib.h"
#include "Audio.h"
#include "Graphics.h"
#include "Utility.h"

LoadAudio::LoadAudio()
{
	
}

LoadAudio::~LoadAudio()
{

}

void LoadAudio::Load(const std::string & name, bool loop, IXAudio2* xaudio2)
{
	// サウンドファイルの登録
	m_Filename = name;
	m_Loop = loop;

	HRESULT hr = S_OK;;
	HANDLE hFile;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	// バッファのクリア
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// サウンドデータファイルの生成
	hFile = CreateFile(m_Filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		ThrowIfFailed(hr, "サウンドデータファイルの生成に失敗(1)");
		return;
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		ThrowIfFailed(hr, "サウンドデータファイルの生成に失敗(2)");
		return;
	}

	// WAVEファイルのチェック
	hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "WAVEファイルのチェックに失敗！(1)");
		return;
	}
	hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "WAVEファイルのチェックに失敗！(2)");
		return;
	}
	if (dwFiletype != 'EVAW')
	{
		ThrowIfFailed(hr, "WAVEファイルのチェックに失敗！(3)");
		return;
	}

	// フォーマットチェック
	hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "フォーマットチェックに失敗！(1)");
		return;
	}
	hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "フォーマットチェックに失敗！(2)");
		return;
	}

	// オーディオデータ読み込み
	hr = CheckChunk(hFile, 'atad', &m_sizeAudio, &dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "オーディオデータ読み込みに失敗！(1)");
		return;
	}
	m_dataAudio = (BYTE*)malloc(m_sizeAudio);
	hr = ReadChunkData(hFile, m_dataAudio, m_sizeAudio, dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "オーディオデータ読み込みに失敗！(2)");
		return;
	}

	// ソースボイスの生成
	hr = xaudio2->CreateSourceVoice(&m_sourceVoice, &(wfx.Format));
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "ソースボイスの生成に失敗！");
		return;
	}

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_sizeAudio;
	buffer.pAudioData = m_dataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	m_Loop ? buffer.LoopCount = -1 : buffer.LoopCount = 0;

	// オーディオバッファの登録
	m_sourceVoice->SubmitSourceBuffer(&buffer);
}

void LoadAudio::Unload()
{
	if (m_sourceVoice)
	{
		// 一時停止
		m_sourceVoice->Stop(0);

		// ソースボイスの破棄
		m_sourceVoice->DestroyVoice();
		m_sourceVoice = NULL;

		// オーディオデータの開放
		free(m_dataAudio);
		m_dataAudio = NULL;
	}
}

void LoadAudio::Play()
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_sizeAudio;
	buffer.pAudioData = m_dataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	m_Loop ? buffer.LoopCount = -1 : buffer.LoopCount = 0;

	// 状態取得
	m_sourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
	 // 一時停止
		m_sourceVoice->Stop(0);

		// オーディオバッファの削除
		m_sourceVoice->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	m_sourceVoice->SubmitSourceBuffer(&buffer);

	// 再生
	m_sourceVoice->Start(0);
}

void LoadAudio::Stop()
{
	if (m_sourceVoice)
	{
		// 一時停止
		m_sourceVoice->Stop(0);
	}
}

void LoadAudio::SetVolume(float volume)
{
	// ボリュームが1.0fより大きくならないようにする
	float v = Math::Min(volume, 1.0f);
	m_sourceVoice->SetVolume(v);
}

HRESULT LoadAudio::CheckChunk(HANDLE hFile, DWORD format, DWORD * pChunkSize, DWORD * pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

HRESULT LoadAudio::ReadChunkData(HANDLE hFile, void * pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}
	return S_OK;
}

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
