/*-------------------------------------------------------------

	[Texture.h]
	Author : o‡ãÄ‘¾

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
	auto itr = m_Map.find(Tag);
	if (itr != m_Map.end())
	{
		return itr->second->GetTexture().Get();
	}
	else
	{
		throw std::domain_error("Not find Texture");
	}
}

void Texture::Load(const std::string & Tag, const std::string & FileName)
{
	const std::string file = "Asset/Texture/" + FileName;
	m_Map[Tag] = std::make_unique<LoadTexture>();
	m_Map[Tag]->Load(file);
}

void Texture::Unload(const std::string & Tag)
{
	auto itr = m_Map.find(Tag);
	if (itr != m_Map.end())
	{
		itr = m_Map.erase(itr);
	}
}
