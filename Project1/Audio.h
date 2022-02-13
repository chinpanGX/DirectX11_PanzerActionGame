/*-----------------------------------------------------------

	[Audio.h]
	Author : 出合翔太

------------------------------------------------------------*/
#pragma once
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

class Audio final
{
public:
	Audio();
	~Audio();
	void Load(const std::string& Name, bool Loop);
	void Unload(const std::string& Name);
	void Unload();
	void Play(const std::string& Tag, float Volume = 1.0f);
	void Stop();
	void SetVolume(const std::string& Name, float volume);
private:
	std::unordered_map<std::string, std::unique_ptr<LoadAudio>> m_Map;
	IXAudio2* m_xAudio2;
	IXAudio2MasteringVoice* m_masteringVoice;
};