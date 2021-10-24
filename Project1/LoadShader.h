/*-------------------------------------------------------------
	
	[LoadShader.h]
	Author : 出合翔太

	シェーダーファイルの読み込み

--------------------------------------------------------------*/
#pragma once
#include "Loader.h"

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


/*
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
};*/