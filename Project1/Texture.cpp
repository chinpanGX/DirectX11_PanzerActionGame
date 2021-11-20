/*-------------------------------------------------------------

	[Texture.h]
	Author : 出合翔太

--------------------------------------------------------------*/
#include "Engine.h"
#include "Graphics.h"
#include "Texture.h"
#include "Utility.h"

LoadTexture::LoadTexture()
{
	
}

LoadTexture::~LoadTexture()
{

}

void LoadTexture::Load(const std::string& name)
{ 
	// テクスチャの読み込み
	D3DX11CreateShaderResourceViewFromFile(Engine::Get().graphics()->GetDevice().Get(), (LPSTR)name.c_str(), NULL, NULL, m_Texture.GetAddressOf(), NULL);
	assert(m_Texture);
}

const  Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> LoadTexture::GetTexture() const
{
	return m_Texture;
}

Texture::Texture()
{

}

Texture::~Texture()
{
	m_Map.clear();
}

ID3D11ShaderResourceView * Texture::GetTexture(const std::string & Tag)
{
	// タグからテクスチャを探す
	auto itr = m_Map.find(Tag);
	// 見つかれば返す
	if (itr != m_Map.end())
	{
		return itr->second->GetTexture().Get();
	}
	else
	{
		// 見つからないときはエラー処理
		throw std::domain_error("Not find Texture");
	}
}

// ロード処理
void Texture::Load(const std::string & Tag, const std::string & FileName)
{
	const std::string file = "Asset/Texture/" + FileName;
	m_Map[Tag] = std::make_unique<LoadTexture>();
	m_Map[Tag]->Load(file);
}

// 該当するテクスチャを削除
void Texture::Unload(const std::string & Tag)
{
	// タグから探す
	auto itr = m_Map.find(Tag);
	// 見つかれば削除
	if (itr != m_Map.end())
	{
		itr = m_Map.erase(itr);
	}
	else
	{
		// 見つからないときはエラー処理
		throw std::domain_error("Not find Texture");
	}
}