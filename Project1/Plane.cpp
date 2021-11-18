/*------------------------------------------------------------

	[Plane.cpp]
	Author : 出合翔太

--------------------------------------------------------------*/
#include "Resource.h"
#include "Engine.h"
#include "Renderer3D.h"
#include "Grass.h"
#include "Plane.h"

namespace
{
	// ラインの数
	const uint32_t g_LineNum = g_BlockNum + 1;
	// インデックスの数
	const uint32_t g_IndexNum = ((g_BlockNum + 2) * 2) * g_BlockNum - 2;
	// ブロックの最後の番号
	const uint32_t g_LastBlock = g_BlockNum - 1;
}

Plane::Plane() : m_Graphics(*Engine::Get().graphics())
{
	// 頂点情報の設定
	for (int x = 0; x <= g_BlockNum; x++)
	{
		for (int z = 0; z <= g_BlockNum; z++)
		{
			m_Vertex[x][z].Position = D3DXVECTOR3((x - 50.0f) * 5.0f, 0.0f, (z - 50.0f) * -5.0f);
			m_Vertex[x][z].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_Vertex[x][z].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			m_Vertex[x][z].TexCoord = D3DXVECTOR2(x * 100.0f, z * 100.0f);
		}
	}

	// 頂点バッファ生成
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.ByteWidth = sizeof(Vertex3D) * g_LineNum * g_LineNum;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA vsd;
	ZeroMemory(&vsd, sizeof(vsd));
	vsd.pSysMem = m_Vertex;

	m_Graphics.GetDevice()->CreateBuffer(&vbd, &vsd, m_VertexBuffer.GetAddressOf());
	
	// インデックスバッファ生成
	unsigned int index[g_IndexNum];
	int i = 0;
	for (int x = 0; x < g_BlockNum; x++) // ブロック数
	{
		for (int z = 0; z < g_LineNum; z++) // ライン数
		{
			index[i] = x * g_LineNum + z;
			i++;
			index[i] = (x + 1) * g_LineNum + z;
			i++;
		}

		// ブロックの最後
		if (x == g_LastBlock)
		{
			break;
		}

		// 縮退ポリゴンのインデックス
		index[i] = (x + 1) * g_LineNum + g_BlockNum;
		i++;

		index[i] = (x + 1) * g_LineNum;
		i++;
	}

	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth = sizeof(unsigned int) * g_IndexNum;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA isd;
	ZeroMemory(&isd, sizeof(isd));
	isd.pSysMem = index;
	m_Graphics.GetDevice()->CreateBuffer(&ibd, &isd, m_IndexBuffer.GetAddressOf());

	// Transformの追加
	m_Transform = AddComponent<Transform>();
	m_Transform->scale(1000.0f);
}

Plane::~Plane()
{
	
}

void Plane::Begin()
{
	
}

void Plane::Update()
{
	
}

void Plane::Event()
{
}

void Plane::Draw()
{
	resource().SetShader("NoLighting");
	
	resource().SetTexture(0, "Grass");
	
	UINT stride = sizeof(Vertex3D);
	UINT offset = 0;
	m_Graphics.GetDeviceContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);
	
	// マトリクスの計算
	Actor::UpdateMatrix(*m_Transform);
	
	// インデックス
	m_Graphics.GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	// マテリアル設定
	Material material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Graphics.SetMaterial(material);

	// プリミティブトポロジ設定
	m_Graphics.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	m_Graphics.GetDeviceContext()->DrawIndexed(g_IndexNum, 0, 0);
}

