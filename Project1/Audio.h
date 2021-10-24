/*-----------------------------------------------------------

	[Audio.h]
	Author : 出合翔太

------------------------------------------------------------*/
#pragma once
#include "xaudio2.h"
#include "Loader.h"

namespace Prefabs
{
	// ラベル名の列挙
	enum Sound
	{
		SHOT,
		IDLE,
		BGM, // 選択BGM
		CANCEL, // キャンセル
		BUTTON, // ボタン音
		SELECT, // 選択
		ENTER, // 決定
		BGM_02,
		BEGIN_SE,
		BGM_WIN,
		BGM_LOSE,

		// ゲームBGM
		BGM_DE_01,
		BGM_DE_02,
		BGM_UK_01,
		BGM_US_01,
		BGM_US_02,
		BGM_RF_01,
		LABEL_MAX
	};

}

class LoadAudio final
{
public:
	LoadAudio();
	~LoadAudio();
	void Load(const std::string& name, bool loop, IXAudio2* xaudio2);
	void Unload();
	void Play();
	void Stop();
	void SetVolume(float volume);
private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	std::string m_Filename;	// ファイル名
	DWORD m_sizeAudio;
	IXAudio2SourceVoice* m_sourceVoice;
	BYTE* m_dataAudio;
	bool m_Loop;		// true　ループ / false 1回
};

class Audio final
{
public:
	Audio();
	~Audio();
	void Load(const std::string& name, bool loop);
	void Unload(const std::string& name);
	void Unload();
	void Play(const std::string& tag, float volume = 1.0f);
	void Stop();
	void SetVolume(const std::string& name, float volume);
private:
	std::unordered_map<std::string, std::unique_ptr<LoadAudio>> m_Map;
	IXAudio2* m_xAudio2;
	IXAudio2MasteringVoice* m_masteringVoice;
};