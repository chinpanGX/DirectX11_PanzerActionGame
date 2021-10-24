/*-------------------------------------------------------------
	
	[Texture.h]
	Author : 出合翔太

--------------------------------------------------------------*/
#pragma once
#include "Loader.h"
#include <vector>

class LoadTexture final : public Loader
{
public:
	LoadTexture();
	~LoadTexture();
	void Load(const std::string& name)override;
	const ComPtr<ID3D11ShaderResourceView> GetTexture()const;
private:
	ComPtr<ID3D11ShaderResourceView> m_Texture;
};

// Textureのプレハブ
class Texture final
{
public:
	Texture();
	~Texture();
	ID3D11ShaderResourceView* GetTexture(const std::string& Tag);
	void Load(const std::string& Tag, const std::string& FileName);
	void Unload(const std::string& Tag);
private:
	std::unordered_map<std::string, std::unique_ptr<LoadTexture>> m_Map;
};

