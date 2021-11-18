/*-------------------------------------------------------------
	
	[Texture.h]
	Author : �o���đ�

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

// Texture�̃v���n�u
class Texture final
{
public:
	Texture();
	~Texture();
	ID3D11ShaderResourceView* GetTexture(const std::string& Tag);
	void Load(const std::string& Tag, const std::string& FileName);
	void Unload(const std::string& Tag);
	void Unload();
private:
	std::unordered_map<std::string, std::unique_ptr<LoadTexture>> m_Map;
};

