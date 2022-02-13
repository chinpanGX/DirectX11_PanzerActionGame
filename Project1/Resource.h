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
	Resource(Graphics& Graphics);
	~Resource();

	// テクスチャのロード
	void LoadTexture(const std::string& Tag, const std::string& FileName);
	void UnloadTexture(const std::string& Tag);

	// 共通で使うリソースのロード・アンロード
	void LoadTexture_ThreadA();
	void LoadTexture_ThreadB();	
	void LoadModel_ThreadA();
	void Unload();
	
	// モデルのロード
	void LoadModel(const std::string& Tag, const std::string& FileName);
	void UnloadModel(const std::string& Tag);

	//　オーディオ
	void AudioLoad(const std::string& Tag, bool Loop);
	void AudioUnload();	// アンロード

	// オーディオの操作
	void AudioPlay(const std::string& Tag, float Volume = 1.0f);
	void AudioStop();
	void AudioSetVolume(const std::string& Tag, float Volume);

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


