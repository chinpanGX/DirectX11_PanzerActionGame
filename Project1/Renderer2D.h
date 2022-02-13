/*--------------------------------------------------------

	[Renderer2D.h]
	Author : �o���đ�

---------------------------------------------------------*/
#pragma once
#include "myLib.h"


class Graphics;
class Resource;
class Renderer2D final
{
public:
	Renderer2D() = delete;
	// �e�N�X�`���̂ݐݒ�
	Renderer2D(Graphics& Graphics, Resource& resource, const std::string& Tag);
	// �v���p�e�B�ݒ�����ׂĐݒ�
	Renderer2D(Graphics& Graphics, Resource& resource, const std::string& Tag, const D3DXVECTOR2& pos, const D3DXVECTOR2& size, 
		const D3DXVECTOR2& ul = D3DXVECTOR2(0.0f, 0.0f), const D3DXVECTOR2& lr = D3DXVECTOR2(1.0f, 1.0f));
	~Renderer2D();

	// ���_����ݒ肷��
	void SetVertex(const D3DXVECTOR2& pos, const D3DXVECTOR2& size, const D3DXVECTOR2& ul = D3DXVECTOR2(0.0f, 0.0f), const D3DXVECTOR2& lr = D3DXVECTOR2(1.0f, 1.0f), const D3DXVECTOR4& color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	// �ʏ�̕`��
	void Draw();
	// ���l��ύX���ĕ`��
	void Draw(float alpha);
	// �|���S���̃J���[��ύX
	void Draw(const D3DXVECTOR4& color);
	// map,unmap�����ĕ`��
	void Draw(const D3DXVECTOR2& pos, const D3DXVECTOR2& size, const D3DXVECTOR2& ul = D3DXVECTOR2(0.0f, 0.0f), const D3DXVECTOR2& lr = D3DXVECTOR2(1.0f, 1.0f), 
		const D3DXVECTOR4& color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), bool ShaderSetting = true);
private:
	Graphics& m_Graphics;
	Resource& m_Resource;
	std::string m_Texture;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
};

class Render
{
public:
	Render() = delete;
	Render(Graphics& Graphics, Resource& resource);
	~Render();
	void Draw(float param, const D3DXVECTOR2& pos, const D3DXVECTOR4& color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	void Draw(float param, const D3DXVECTOR2& pos, float size_y, const std::string& texture, const D3DXVECTOR4& color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
private:
	Graphics& m_Graphics;
	Resource& m_Resource;
	std::string m_Texture;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
};
