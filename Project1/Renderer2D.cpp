/*-----------------------------------------------------------

	[Renderer2D.cpp]
	Author : 出合翔太

------------------------------------------------------------*/
#include "Graphics.h"
#include "Resource.h"
#include "Engine.h"
#include "Renderer2D.h"
#include "Utility.h"

Renderer2D::Renderer2D(Graphics & graphics, Resource& resource, const std::string& Tag) 
	: m_Graphics(graphics), m_Resource(resource), m_Texture(Tag)
{
	Vertex3D vertex[4];
	vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	//頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	auto hr = m_Graphics.GetDevice()->CreateBuffer(&bd, &sd, m_VertexBuffer.GetAddressOf());
	ThrowIfFailed(hr, "m_VertexBuffer is Failed");
}

Renderer2D::Renderer2D(Graphics & graphics, Resource & resource, const std::string & Tag, const D3DXVECTOR2 & pos, const D3DXVECTOR2 & size, const D3DXVECTOR2 & ul, const D3DXVECTOR2 & lr)
	: m_Graphics(graphics), m_Resource(resource), m_Texture(Tag)
{
	Vertex3D vertex[4];
	vertex[0].Position = D3DXVECTOR3(pos.x - size.x * 0.5f, pos.y - size.y * 0.5f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(ul.x, ul.y);

	vertex[1].Position = D3DXVECTOR3(pos.x + size.x * 0.5f, pos.y - size.y * 0.5f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(lr.x, ul.y);

	vertex[2].Position = D3DXVECTOR3(pos.x - size.x * 0.5f, pos.y + size.y * 0.5f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(ul.x, lr.y);

	vertex[3].Position = D3DXVECTOR3(pos.x + size.x * 0.5f, pos.y + size.y * 0.5f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(lr.x, lr.y);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	auto hr = m_Graphics.GetDevice()->CreateBuffer(&bd, &sd, m_VertexBuffer.GetAddressOf());
	ThrowIfFailed(hr, "m_VertexBuffer is Failed");
}

Renderer2D::~Renderer2D()
{

}

void Renderer2D::SetVertex(const D3DXVECTOR2 & pos, const D3DXVECTOR2 & size, const D3DXVECTOR2 & ul, const D3DXVECTOR2 & lr)
{
	Vertex3D vertex[4];
	vertex[0].Position = D3DXVECTOR3(pos.x - size.x * 0.5f, pos.y - size.y * 0.5f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(ul.x, ul.y);

	vertex[1].Position = D3DXVECTOR3(pos.x + size.x * 0.5f, pos.y - size.y * 0.5f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(lr.x, ul.y);

	vertex[2].Position = D3DXVECTOR3(pos.x - size.x * 0.5f, pos.y + size.y * 0.5f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(ul.x, lr.y);

	vertex[3].Position = D3DXVECTOR3(pos.x + size.x * 0.5f, pos.y + size.y * 0.5f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(lr.x, lr.y);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	m_Graphics.GetDevice()->CreateBuffer(&bd, &sd, m_VertexBuffer.GetAddressOf());
}

void Renderer2D::Draw()
{
	// シェーダーの設定
	m_Resource.SetShader("NoLighting");

	//マトリクス設定
	m_Graphics.SetWorldViewProjection2D();

	//頂点バッファ設定
	UINT stride = sizeof(Vertex3D);
	UINT offset = 0;
	m_Graphics.GetDeviceContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);

	//マテリアル設定
	Material material;
	material.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Graphics.SetMaterial(material);

	//テクスチャ設定
	m_Resource.SetTexture(0, m_Texture);

	//プリミティブトポロジ設定
	m_Graphics.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	m_Graphics.GetDeviceContext()->Draw(4, 0);
}

void Renderer2D::Draw(float alpha)
{
	// シェーダーの設定
	m_Resource.SetShader("Default");

	//マトリクス設定
	m_Graphics.SetWorldViewProjection2D();

	//頂点バッファ設定
	UINT stride = sizeof(Vertex3D);
	UINT offset = 0;
	m_Graphics.GetDeviceContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);

	//マテリアル設定
	Material material;
	material.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, alpha);
	m_Graphics.SetMaterial(material);

	//テクスチャ設定
	m_Resource.SetTexture(0, m_Texture);

	//プリミティブトポロジ設定
	m_Graphics.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	m_Graphics.GetDeviceContext()->Draw(4, 0);
}

void Renderer2D::Draw(const D3DXVECTOR4& color)
{
	// シェーダーの設定
	m_Resource.SetShader("Defualt");

	//マトリクス設定
	m_Graphics.SetWorldViewProjection2D();

	//頂点バッファ設定
	UINT stride = sizeof(Vertex3D);
	UINT offset = 0;
	m_Graphics.GetDeviceContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);

	//マテリアル設定
	Material material;
	material.Diffuse = D3DXVECTOR4(color);
	m_Graphics.SetMaterial(material);

	//テクスチャ設定
	m_Resource.SetTexture(0, m_Texture);

	//プリミティブトポロジ設定
	m_Graphics.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	m_Graphics.GetDeviceContext()->Draw(4, 0);
}

void Renderer2D::Draw(const D3DXVECTOR2& pos, const D3DXVECTOR2& size, const D3DXVECTOR2& ul, const D3DXVECTOR2& lr, const D3DXVECTOR4& color)
{
	// シェーダーの設定
	m_Resource.SetShader("NoLighting");

	D3D11_MAPPED_SUBRESOURCE msr;
	m_Graphics.GetDeviceContext()->Map(m_VertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	Vertex3D* vertex = (Vertex3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(pos.x - size.x * 0.5f, pos.y - size.y * 0.5f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = color;
	vertex[0].TexCoord = D3DXVECTOR2(ul.x, ul.y);

	vertex[1].Position = D3DXVECTOR3(pos.x + size.x * 0.5f, pos.y - size.y * 0.5f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = color;
	vertex[1].TexCoord = D3DXVECTOR2(lr.x, ul.y);

	vertex[2].Position = D3DXVECTOR3(pos.x - size.x * 0.5f, pos.y + size.y * 0.5f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = color;
	vertex[2].TexCoord = D3DXVECTOR2(ul.x, lr.y);

	vertex[3].Position = D3DXVECTOR3(pos.x + size.x * 0.5f, pos.y + size.y * 0.5f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = color;
	vertex[3].TexCoord = D3DXVECTOR2(lr.x, lr.y);

	m_Graphics.GetDeviceContext()->Unmap(m_VertexBuffer.Get(), 0);

	//マトリクス設定
	m_Graphics.SetWorldViewProjection2D();

	//頂点バッファ設定
	UINT stride = sizeof(Vertex3D);
	UINT offset = 0;
	m_Graphics.GetDeviceContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);


	//テクスチャ設定
	m_Resource.SetTexture(0, m_Texture);

	//プリミティブトポロジ設定
	m_Graphics.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	m_Graphics.GetDeviceContext()->Draw(4, 0);
}

Render::Render(Graphics & graphics, Resource & resource) : m_Graphics(graphics), m_Resource(resource)
{
	Vertex3D vertex[4];
	vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	m_Graphics.GetDevice()->CreateBuffer(&bd, &sd, m_VertexBuffer.GetAddressOf());
}

Render::~Render()
{
}

void Render::Draw(float Param, const D3DXVECTOR2 & pos, const D3DXVECTOR4 & color, const std::string& texture)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	m_Graphics.GetDeviceContext()->Map(m_VertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	Vertex3D* vertex = (Vertex3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(pos.x, pos.y - 10.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = color;
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(pos.x + Param, pos.y - 10.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = color;
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(pos.x, pos.y + 10.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = color;
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(pos.x + Param, pos.y + 10.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = color;
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	m_Graphics.GetDeviceContext()->Unmap(m_VertexBuffer.Get(), 0);

	// シェーダーの設定
	m_Resource.SetShader("NoLighting");

	//マトリクス設定
	m_Graphics.SetWorldViewProjection2D();

	//頂点バッファ設定
	UINT stride = sizeof(Vertex3D);
	UINT offset = 0;
	m_Graphics.GetDeviceContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);

	//テクスチャ設定
	m_Resource.SetTexture(0, texture);

	//プリミティブトポロジ設定
	m_Graphics.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	m_Graphics.GetDeviceContext()->Draw(4, 0);
}
