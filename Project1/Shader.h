/*--------------------------------------------------------------

	[Shader.h]
	Author : �o���đ�

---------------------------------------------------------------*/
#pragma once
#include "Loader.h"

class VertexShader final
{
public:
	VertexShader() = delete;
	VertexShader(Graphics& Graphics);
	~VertexShader();
	ID3D11VertexShader* GetVertexShader(const std::string& Tag);
	ID3D11InputLayout* GetInputLayout(const std::string& Tag);
private:
	std::unordered_map<std::string, std::unique_ptr<LoadVertexShader>> m_Map;
};

// �s�N�Z���V�F�[�_�[
class PixelShader final
{
public:
	PixelShader() = delete;
	PixelShader(Graphics& Graphics);
	~PixelShader();
	ID3D11PixelShader* GetPixelShader(const std::string& Tag);
private:
	std::unordered_map<std::string, std::unique_ptr<LoadPixelShader>> m_Map;
};

#if 0
class GeometryShader final
{
public:
	// �W�I���g���V�F�[�_�[
	GeometryShader();
	GeometryShader(Graphics& Graphics);
	~GeometryShader();
	ID3D11GeometryShader* GetGeometryShader();
private:
	std::unique_ptr<LoadGeometryShader> m_GeometryShader;
};

// �R���s���[�g�V�F�[�_�[
class ComputeShader final
{
public:
	ComputeShader();
	ComputeShader(Graphics& Graphics);
	~ComputeShader();
	ID3D11ComputeShader* GetComputeShader();
private:
	std::unique_ptr<LoadComputeShader> m_ComputeShader;
};
#endif