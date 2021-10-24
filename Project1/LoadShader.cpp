/*-------------------------------------------------------------

	[LoadShader.h]
	Author : 出合翔太

	シェーダーファイルの読み込み

--------------------------------------------------------------*/
#include "stdafx.h"
#include "Utility.h"
#include "LoadShader.h"
#include <io.h>

// 頂点シェーダー
LoadVertexShader::LoadVertexShader(Graphics & graphics) : m_Graphics(graphics), m_VertexShader(nullptr), m_InputLayout(nullptr)
{
	
}

LoadVertexShader::~LoadVertexShader()
{

}

void LoadVertexShader::Load(const std::string& name)
{
	FILE* file;
	long int fsize;
	file = fopen(name.c_str(), "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);
	auto hr = m_Graphics.GetDevice()->CreateVertexShader(buffer, fsize, nullptr, m_VertexShader.GetAddressOf());
	ThrowIfFailed(hr, "CreateVertexShader Failed");

	// 入力レイアウト生成
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);
	hr = m_Graphics.GetDevice()->CreateInputLayout(layout, numElements, buffer, fsize, m_InputLayout.GetAddressOf());
	ThrowIfFailed(hr, "CreateInputLayout Failed");
	delete[] buffer;
}

Microsoft::WRL::ComPtr<ID3D11VertexShader> LoadVertexShader::GetVertexShader() const
{
	return m_VertexShader;
}

Microsoft::WRL::ComPtr<ID3D11InputLayout> LoadVertexShader::GetInputLayout() const
{
	return m_InputLayout;
}

LoadPixelShader::LoadPixelShader(Graphics & graphics) : m_Graphics(graphics), m_PixelShader(nullptr)
{
}

LoadPixelShader::~LoadPixelShader()
{

}

void LoadPixelShader::Load(const std::string& name)
{
	FILE* file;
	long int fsize;
	file = fopen(name.c_str(), "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);
	auto hr = m_Graphics.GetDevice()->CreatePixelShader(buffer, fsize, nullptr, m_PixelShader.GetAddressOf());
	ThrowIfFailed(hr, "CreatePixelShader Failed");
	delete[] buffer;
}

Microsoft::WRL::ComPtr<ID3D11PixelShader> LoadPixelShader::GetPixelShader() const
{
	return m_PixelShader;
}
