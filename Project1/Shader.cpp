/*--------------------------------------------------------------

	[Shader.cpp]
	Author : �o���đ�

---------------------------------------------------------------*/
#include "Shader.h"
#include <vector>

namespace
{
	enum ShaderID : int32_t
	{
		DEFAULT,
		NOLIGHTING, // ���C�e�B���O�Ȃ�
		MAPPING,
		SHADERMAX
	};
}

VertexShader::VertexShader(Graphics & graphics)
{
	std::string assetname = "Asset/Shader/";

	// �������m�ہA�^�O�o�^�ƃ��[�h
	m_Map["Default"] = std::make_unique<LoadVertexShader>(graphics);
	m_Map["NoLighting"] = std::make_unique<LoadVertexShader>(graphics);
	m_Map["Mapping"] = std::make_unique<LoadVertexShader>(graphics);
	m_Map["SpotLight"] = std::make_unique<LoadVertexShader>(graphics);

	m_Map["Default"]->Load(assetname + "vertexLightingVS.cso");
	m_Map["NoLighting"]->Load(assetname + "unlitTextureVS.cso");
	m_Map["Mapping"]->Load(assetname + "MappingVS.cso");	
	m_Map["SpotLight"]->Load(assetname + "SpotLightVS.cso");
}

VertexShader::~VertexShader()
{

}

ID3D11VertexShader * VertexShader::GetVertexShader(const std::string & Tag)
{
	return m_Map[Tag]->GetVertexShader().Get();
}

ID3D11InputLayout * VertexShader::GetInputLayout(const std::string & Tag)
{
	return m_Map[Tag]->GetInputLayout().Get();
}

PixelShader::PixelShader(Graphics & graphics)
{
	std::string assetname = "Asset/Shader/";
	
	// �������m�ہA�^�O�o�^�ƃ��[�h
	m_Map["Default"] = std::make_unique<LoadPixelShader>(graphics);
	m_Map["NoLighting"] = std::make_unique<LoadPixelShader>(graphics);
	m_Map["Mapping"] = std::make_unique<LoadPixelShader>(graphics);
	m_Map["SpotLight"] = std::make_unique<LoadPixelShader>(graphics);
	
	m_Map["Default"]->Load(assetname + "vertexLightingPS.cso");
	m_Map["NoLighting"]->Load(assetname + "unlitTexturePS.cso");
	m_Map["Mapping"]->Load(assetname + "MappingPS.cso");
	m_Map["SpotLight"]->Load(assetname + "SpotLightPS.cso");
}

PixelShader::~PixelShader()
{

}

ID3D11PixelShader * PixelShader::GetPixelShader(const std::string & Tag)
{
	return m_Map[Tag]->GetPixelShader().Get();
}
