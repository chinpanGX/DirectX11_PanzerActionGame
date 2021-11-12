/*----------------------------------------------------------
	
	[Renderer3D.cpp]
	Author : 出合翔太

-----------------------------------------------------------*/
#include "Graphics.h"
#include "Renderer3D.h"

Renderer3D::Renderer3D(Graphics& graphics, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale) 
	: m_Graphics(graphics), m_VertexBuffer(nullptr), m_Position(pos), m_Rotation(rot), m_Scale(scale)
{
	
}

Renderer3D::~Renderer3D()
{
}

void Renderer3D::Update(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
{
	m_Position = pos;
	m_Rotation = rot;
	m_Scale = scale;
	UpdeteMatrix();
}

void Renderer3D::Draw()
{
	// 頂点バッファ設定
	UINT stride = sizeof(Vertex3D);
	UINT offset = 0;
	m_Graphics.GetDeviceContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);
	// マテリアル設定
	Material material;
	material.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Graphics.SetMaterial(material);

	// プリミティブトポロジ設定
	m_Graphics.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	m_Graphics.GetDeviceContext()->Draw(4, 0);
}

void Renderer3D::CreatePlane(float distance, int uvtiling, D3DXVECTOR2 tex)
{
	float pos = distance;
	float w = tex.x * (float)uvtiling;
	float h = tex.y * (float)uvtiling;
	Vertex3D Vertex[4];
	Vertex[0].Position = D3DXVECTOR3(-pos, 0.0f, pos);
	Vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	Vertex[1].Position = D3DXVECTOR3(pos, 0.0f, pos);
	Vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[1].TexCoord = D3DXVECTOR2(w, 0.0f);

	Vertex[2].Position = D3DXVECTOR3(-pos, 0.0f, -pos);
	Vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[2].TexCoord = D3DXVECTOR2(0.0f, h);

	Vertex[3].Position = D3DXVECTOR3(pos, 0.0f, -pos);
	Vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[3].TexCoord = D3DXVECTOR2(w, h);

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = Vertex;
	m_Graphics.GetDevice()->CreateBuffer(&bd, &sd, m_VertexBuffer.GetAddressOf());
}

void Renderer3D::CreateWall(float distance, int uvtiling, D3DXVECTOR2 tex)
{
	float pos = distance;
	float w = tex.x * (float)uvtiling;
	float h = tex.y * (float)uvtiling;
	Vertex3D Vertex[4];
	Vertex[0].Position = D3DXVECTOR3(-pos, pos, 0.0f);
	Vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	Vertex[1].Position = D3DXVECTOR3(pos, pos, 0.0f);
	Vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[1].TexCoord = D3DXVECTOR2(w, 0.0f);

	Vertex[2].Position = D3DXVECTOR3(-pos, -pos, 0.0f);
	Vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[2].TexCoord = D3DXVECTOR2(0.0f, h);

	Vertex[3].Position = D3DXVECTOR3(pos, -pos, 0.0f);
	Vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[3].TexCoord = D3DXVECTOR2(w, h);

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = Vertex;
	m_Graphics.GetDevice()->CreateBuffer(&bd, &sd, m_VertexBuffer.GetAddressOf());
}

void Renderer3D::UpdeteMatrix()
{
	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	m_Graphics.SetWorldMatrix(world);
}
