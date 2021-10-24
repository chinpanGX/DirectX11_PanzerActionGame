/*------------------------------------------------------------
	
	[Resoruce.h]
	Author : 出合翔太

	リソースを管理

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
	Resource(Graphics& graphics);
	~Resource();

	// テクスチャのロード
	void LoadTexture(const std::string& tag, const std::string& filename);
	void UnloadTexture(const std::string& tag);
	void LoadTexture_ThreadA();
	void LoadTexture_ThreadB();

	// モデルのロード
	void LoadModel_ThreadA();
	void LoadModel(const std::string& tag, const std::string& filename);
	void UnloadModel(const std::string& tag);

	//　オーディオ
	void AudioLoad(const std::string& tag, bool loop);
	void AudioUnload();	// アンロード
	void AudioPlay(const std::string& tag, float volume = 1.0f);
	void AudioStop();
	void AudioSetVolume(const std::string& tag, float volume);

	// テクスチャ
	void SetTexture(int slot, const std::string& Tag); // slot = 設定するスロット、ID = 格納ID

	// シェーダーをまとめて設定する
	void SetShader(const std::string& Tag);

	// 頂点シェーダー
	void SetVertexShader(const std::string& Tag);
	void SetInputLayout(const std::string& Tag);
	// ピクセルシェーダー
	void SetPixelShader(const std::string& Tag);

	// モデル
	void SetStaticModel(const std::string& Tag);

private:
	Graphics& m_Graphics;
	std::unique_ptr<Audio> m_Audio;
	std::unique_ptr<Texture> m_Texture;
	std::unique_ptr<VertexShader> m_VertexShader;
	std::unique_ptr<PixelShader> m_PixelShader;
	std::unique_ptr<Prefabs::ModelPool> m_StaticModel;
};


