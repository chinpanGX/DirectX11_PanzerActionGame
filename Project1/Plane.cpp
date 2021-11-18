/*------------------------------------------------------------

	[Plane.cpp]
	Author : �o���đ�

--------------------------------------------------------------*/
#include "Resource.h"
#include "Engine.h"
#include "Renderer3D.h"
#include "Grass.h"
#include "Plane.h"

namespace
{
	// ���C���̐�
	const uint32_t g_LineNum = g_BlockNum + 1;
	// �C���f�b�N�X�̐�
	const uint32_t g_IndexNum = ((g_BlockNum + 2) * 2) * g_BlockNum - 2;
	// �u���b�N�̍Ō�̔ԍ�
	const uint32_t g_LastBlock = g_BlockNum - 1;
}

Plane::Plane() : m_Graphics(*Engine::Get().graphics())
{
	// ���_���̐ݒ�
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

	// ���_�o�b�t�@����
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
	
	// �C���f�b�N�X�o�b�t�@����
	unsigned int index[g_IndexNum];
	int i = 0;
	for (int x = 0; x < g_BlockNum; x++) // �u���b�N��
	{
		for (int z = 0; z < g_LineNum; z++) // ���C����
		{
			index[i] = x * g_LineNum + z;
			i++;
			index[i] = (x + 1) * g_LineNum + z;
			i++;
		}

		// �u���b�N�̍Ō�
		if (x == g_LastBlock)
		{
			break;
		}

		// �k�ރ|���S���̃C���f�b�N�X
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

	// Transform�̒ǉ�
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
	
	// �}�g���N�X�̌v�Z
	Actor::UpdateMatrix(*m_Transform);
	
	// �C���f�b�N�X
	m_Graphics.GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	// �}�e���A���ݒ�
	Material material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Graphics.SetMaterial(material);

	// �v���~�e�B�u�g�|���W�ݒ�
	m_Graphics.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	m_Graphics.GetDeviceContext()->DrawIndexed(g_IndexNum, 0, 0);
}

