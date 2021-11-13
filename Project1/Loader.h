/*-------------------------------------------------------------
	
	[Loader.h]
	Author : 出合翔太

--------------------------------------------------------------*/
#pragma once
#include "stdafx.h"
#include "Graphics.h"
#include "xaudio2.h"
#include <string>
#include <unordered_map>

class Loader
{
public:
	virtual void Load(const std::string& name) = 0;
protected:
	template< typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
};

// マテリアル構造体
struct ModelMaterial
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Texture;
	Material Material;
	char	 Name[256];
	char	 TextureName[256];
};

// 描画サブセット構造体
struct Sebset
{
	ModelMaterial Material;
	uint32_t StartIndex;
	uint32_t IndexNum;
};

// モデルの情報
struct ModelInfo
{
	Vertex3D* VertexArray;
	uint32_t  VertexNum;

	uint32_t* IndexArray;
	uint32_t  IndexNum;

	Sebset*  SubsetArray;
	uint32_t SubsetNum;
};

// モデル
class Model final : public Loader
{
public:
	Model() = delete;
	Model(Graphics & graphics);
	~Model();
	void Load(const std::string& name)override;
	void Unload();
	void Draw();
private:
	Graphics& m_Graphics;
	ComPtr<ID3D11Buffer> m_VertexBuffer;
	ComPtr<ID3D11Buffer> m_IndexBuffer;

	Sebset*	 m_SubsetArray;
	uint32_t m_SubsetNum;

	void LoadObj(const std::string& FileName, ModelInfo *Model);
	void LoadMaterial(const std::string& FileName, ModelMaterial **MaterialArray, uint32_t *MaterialNum);
};

// 頂点シェーダー
class LoadVertexShader final : public Loader
{
public:
	LoadVertexShader() = delete;
	LoadVertexShader(Graphics & graphics);
	~LoadVertexShader();
	void Load(const std::string& FileName)override;
	ComPtr<ID3D11VertexShader> GetVertexShader() const;
	ComPtr<ID3D11InputLayout> GetInputLayout() const;
private:
	class Graphics& m_Graphics;
	ComPtr<ID3D11VertexShader> m_VertexShader;
	ComPtr<ID3D11InputLayout> m_InputLayout;
};

// ピクセルシェーダー
class LoadPixelShader final : public Loader
{
public:
	LoadPixelShader() = delete;
	LoadPixelShader(Graphics & graphics);
	~LoadPixelShader();
	void Load(const std::string& name)override;
	ComPtr<ID3D11PixelShader> GetPixelShader() const;
private:
	class Graphics& m_Graphics;
	ComPtr<ID3D11PixelShader> m_PixelShader;
};


#if 0
// ジオメトリシェーダー
class LoadGeometryShader final : public Loader
{
public:
	LoadGeometryShader();
	LoadGeometryShader(Graphics & dx, std::string FileName);
	~LoadGeometryShader();
	ComPtr<ID3D11GeometryShader> GetGeometryShader() const;
private:
	void Create(Graphics& dx, ID3D11GeometryShader** Shader, std::string FileName);
	ComPtr<ID3D11GeometryShader> m_GeometryShader;
};

// コンピュートシェーダー
class LoadComputeShader final : public Loader
{
public:
	LoadComputeShader();
	LoadComputeShader(Graphics & dx, std::string FileName);
	~LoadComputeShader();
	ComPtr<ID3D11ComputeShader> GetComputeShader() const;
private:
	void Create(Graphics& dx, ID3D11ComputeShader** Shader, std::string FileName);
	ComPtr<ID3D11ComputeShader> m_ComputeShader;
};
#endif 

// オーディオ
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


