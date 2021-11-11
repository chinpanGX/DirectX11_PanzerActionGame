/*------------------------------------------------------------
	
	[LoadModel.cpp]
	Author : �o���đ�

--------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include "Engine.h"
#include "LoadModel.h"
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

Model::Model(Graphics & graphics) : m_Graphics(graphics), m_VertexBuffer(nullptr), m_IndexBuffer(nullptr)
{

}

Model::~Model()
{
	
}

void Model::Load(const std::string& name)
{
	ModelInfo model;
	LoadObj(name, &model);

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.ByteWidth = sizeof(Vertex3D) * model.VertexNum;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA vsd;
	ZeroMemory(&vsd, sizeof(vsd));
	vsd.pSysMem = model.VertexArray;
	m_Graphics.GetDevice()->CreateBuffer(&vbd, &vsd, m_VertexBuffer.GetAddressOf());
	
	// �C���f�b�N�X�o�b�t�@����
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth = sizeof(uint32_t) * model.IndexNum;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA isd;
	ZeroMemory(&isd, sizeof(isd));
	isd.pSysMem = model.IndexArray;
	m_Graphics.GetDevice()->CreateBuffer(&ibd, &isd, m_IndexBuffer.GetAddressOf());
	
	// �T�u�Z�b�g�ݒ�
	m_SubsetArray = new Sebset[model.SubsetNum];
	m_SubsetNum = model.SubsetNum;

	for (uint32_t i = 0; i < model.SubsetNum; i++)
	{
		m_SubsetArray[i].StartIndex = model.SubsetArray[i].StartIndex;
		m_SubsetArray[i].IndexNum = model.SubsetArray[i].IndexNum;
		m_SubsetArray[i].Material.Material = model.SubsetArray[i].Material.Material;
		D3DX11CreateShaderResourceViewFromFile(Engine::Get().graphics()->GetDevice().Get(), model.SubsetArray[i].Material.TextureName,
			NULL, NULL, m_SubsetArray[i].Material.Texture.GetAddressOf(), NULL);
		assert(m_SubsetArray[i].Material.Texture);
	}
	
	delete[] model.VertexArray;
	delete[] model.IndexArray;
	delete[] model.SubsetArray;
}

void Model::Unload()
{
	delete[] m_SubsetArray;
}

void Model::Draw()
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(Vertex3D);
	UINT offset = 0;
	m_Graphics.GetDeviceContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�ݒ�
	m_Graphics.GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	// �v���~�e�B�u�g�|���W�ݒ�
	m_Graphics.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	for (uint32_t i = 0; i < m_SubsetNum; i++)
	{
		// �}�e���A���ݒ�
		m_Graphics.SetMaterial(m_SubsetArray[i].Material.Material);

		// �e�N�X�`���ݒ�
		m_Graphics.GetDeviceContext()->PSSetShaderResources(0, 1, m_SubsetArray[i].Material.Texture.GetAddressOf());

		// �|���S���`��
		m_Graphics.GetDeviceContext()->DrawIndexed(m_SubsetArray[i].IndexNum, m_SubsetArray[i].StartIndex, 0);
	}
}

void Model::LoadObj(const std::string& FileName, ModelInfo * Model)
{
	char dir[256];
	strcpy(dir, FileName.c_str());
	PathRemoveFileSpec(dir);

	DirectX::XMFLOAT3	*positionArray;
	DirectX::XMFLOAT3	*normalArray;
	DirectX::XMFLOAT2	*texcoordArray;

	uint32_t positionNum = 0;
	uint32_t normalNum = 0;
	uint32_t texcoordNum = 0;
	uint32_t vertexNum = 0;
	uint32_t indexNum = 0;
	uint32_t in = 0;
	uint32_t subsetNum = 0;

	ModelMaterial	*materialArray = NULL;
	uint32_t	materialNum = 0;

	char str[256];
	char *s;
	char c;

	FILE *file;
	file = fopen(FileName.c_str(), "rt");
	if (file == nullptr)
	{
		std::domain_error("�t�@�C�����J���Ȃ�");
	}

	//�v�f���J�E���g
	while (true)
	{
		fscanf(file, "%s", str);
		if (feof(file) != 0)
		{
			break;
		}

		if (strcmp(str, "v") == 0)
		{
			positionNum++;
		}
		else if (strcmp(str, "vn") == 0)
		{
			normalNum++;
		}
		else if (strcmp(str, "vt") == 0)
		{
			texcoordNum++;
		}
		else if (strcmp(str, "usemtl") == 0)
		{
			subsetNum++;
		}
		else if (strcmp(str, "f") == 0)
		{
			in = 0;

			do
			{
				fscanf(file, "%s", str);
				vertexNum++;
				in++;
				c = fgetc(file);
			} while (c != '\n' && c != '\r');

			//�l�p�͎O�p�ɕ���
			if (in == 4)
			{
				in = 6;
			}
			indexNum += in;
		}
	}

	//�������m��
	positionArray = new DirectX::XMFLOAT3[positionNum];
	normalArray = new DirectX::XMFLOAT3[normalNum];
	texcoordArray = new DirectX::XMFLOAT2[texcoordNum];
	Model->VertexArray = new Vertex3D[vertexNum];
	Model->VertexNum = vertexNum;
	Model->IndexArray = new uint32_t[indexNum];
	Model->IndexNum = indexNum;
	Model->SubsetArray = new Sebset[subsetNum];
	Model->SubsetNum = subsetNum;

	//�v�f�Ǎ�
	DirectX::XMFLOAT3 *position = positionArray;
	DirectX::XMFLOAT3 *normal = normalArray;
	DirectX::XMFLOAT2 *texcoord = texcoordArray;

	uint32_t vc = 0;
	uint32_t ic = 0;
	uint32_t sc = 0;

	fseek(file, 0, SEEK_SET);
	
	while (true)
	{
		fscanf(file, "%s", str);
		if (feof(file) != 0)
		{
			break;
		}
		if (strcmp(str, "mtllib") == 0)
		{
			//�}�e���A���t�@�C��
			fscanf(file, "%s", str);

			char path[256];
			strcpy(path, dir);
			strcat(path, "\\");
			strcat(path, str);

			LoadMaterial(path, &materialArray, &materialNum);
		}
		else if (strcmp(str, "o") == 0)
		{
			//�I�u�W�F�N�g��
			fscanf(file, "%s", str);
		}
		else if (strcmp(str, "v") == 0)
		{
			//���_���W
			fscanf(file, "%f", &position->x);
			fscanf(file, "%f", &position->y);
			fscanf(file, "%f", &position->z);
			position++;
		}
		else if (strcmp(str, "vn") == 0)
		{
			//�@��
			fscanf(file, "%f", &normal->x);
			fscanf(file, "%f", &normal->y);
			fscanf(file, "%f", &normal->z);
			normal++;
		}
		else if (strcmp(str, "vt") == 0)
		{
			//�e�N�X�`�����W
			fscanf(file, "%f", &texcoord->x);
			fscanf(file, "%f", &texcoord->y);
			texcoord->y = 1.0f - texcoord->y;
			texcoord++;
		}
		else if (strcmp(str, "usemtl") == 0)
		{
			//�}�e���A��
			fscanf(file, "%s", str);

			if (sc != 0)
			{
				Model->SubsetArray[sc - 1].IndexNum = ic - Model->SubsetArray[sc - 1].StartIndex;
			}
			Model->SubsetArray[sc].StartIndex = ic;

			for (uint32_t i = 0; i < materialNum; i++)
			{
				if (strcmp(str, materialArray[i].Name) == 0)
				{
					Model->SubsetArray[sc].Material.Material = materialArray[i].Material;
					strcpy(Model->SubsetArray[sc].Material.TextureName, materialArray[i].TextureName);
					strcpy(Model->SubsetArray[sc].Material.Name, materialArray[i].Name);

					break;
				}
			}

			sc++;

		}
		else if (strcmp(str, "f") == 0)
		{
			//��
			in = 0;
			do
			{
				fscanf(file, "%s", str);

				s = strtok(str, "/");
				Model->VertexArray[vc].Position = positionArray[atoi(s) - 1];
				if (s[strlen(s) + 1] != '/')
				{
					//�e�N�X�`�����W�����݂��Ȃ��ꍇ������
					s = strtok(NULL, "/");
					Model->VertexArray[vc].TexCoord = texcoordArray[atoi(s) - 1];
				}
				s = strtok(NULL, "/");
				Model->VertexArray[vc].Normal = normalArray[atoi(s) - 1];

				Model->VertexArray[vc].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

				Model->IndexArray[ic] = vc;
				ic++;
				vc++;

				in++;
				c = fgetc(file);
			} while (c != '\n' && c != '\r');

			//�l�p�͎O�p�ɕ���
			if (in == 4)
			{
				Model->IndexArray[ic] = vc - 4;
				ic++;
				Model->IndexArray[ic] = vc - 2;
				ic++;
			}
		}
	}
	if (sc != 0)
	{
		Model->SubsetArray[sc - 1].IndexNum = ic - Model->SubsetArray[sc - 1].StartIndex;
	}
	fclose(file);
	delete[] positionArray;
	delete[] normalArray;
	delete[] texcoordArray;
	delete[] materialArray;
}

void Model::LoadMaterial(const std::string& FileName, ModelMaterial ** MaterialArray, uint32_t * MaterialNum)
{
	char dir[256];
	strcpy(dir, FileName.c_str());
	PathRemoveFileSpec(dir);
	char str[256];

	FILE *file;
	file = fopen(FileName.c_str(), "rt");
	if (file == nullptr)
	{
		std::domain_error("�t�@�C�����J���Ȃ�");
	}

	ModelMaterial *materialArray;
	uint32_t materialNum = 0;

	//�v�f���J�E���g
	while (true)
	{
		fscanf(file, "%s", str);
		if (feof(file) != 0)
		{
			break;
		}
		if (strcmp(str, "newmtl") == 0)
		{
			materialNum++;
		}
	
	}
	//�������m��
	materialArray = new ModelMaterial[materialNum];

	//�v�f�Ǎ�
	int mc = -1;
	fseek(file, 0, SEEK_SET);
	while (true)
	{
		fscanf(file, "%s", str);
		if (feof(file) != 0)
		{
			break;
		}
		if (strcmp(str, "newmtl") == 0)
		{
			//�}�e���A����
			mc++;
			fscanf(file, "%s", materialArray[mc].Name);
			strcpy(materialArray[mc].TextureName, "");

			materialArray[mc].Material.Emission.x = 0.0f;
			materialArray[mc].Material.Emission.y = 0.0f;
			materialArray[mc].Material.Emission.z = 0.0f;
			materialArray[mc].Material.Emission.w = 0.0f;
		}
		else if (strcmp(str, "Ka") == 0)
		{
			//�A���r�G���g
			fscanf(file, "%f", &materialArray[mc].Material.Ambient.x);
			fscanf(file, "%f", &materialArray[mc].Material.Ambient.y);
			fscanf(file, "%f", &materialArray[mc].Material.Ambient.z);
			materialArray[mc].Material.Ambient.w = 1.0f;
		}
		else if (strcmp(str, "Kd") == 0)
		{
			//�f�B�t���[�Y
			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.x);
			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.y);
			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.z);
			materialArray[mc].Material.Diffuse.w = 1.0f;
		}
		else if (strcmp(str, "Ks") == 0)
		{
			//�X�y�L����
			fscanf(file, "%f", &materialArray[mc].Material.Specular.x);
			fscanf(file, "%f", &materialArray[mc].Material.Specular.y);
			fscanf(file, "%f", &materialArray[mc].Material.Specular.z);
			materialArray[mc].Material.Specular.w = 1.0f;
		}
		else if (strcmp(str, "Ns") == 0)
		{
			//�X�y�L�������x
			fscanf(file, "%f", &materialArray[mc].Material.Shininess);
		}
		else if (strcmp(str, "d") == 0)
		{
			//�A���t�@
			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.w);
		}
		else if (strcmp(str, "map_Kd") == 0)
		{
			//�e�N�X�`��
			fscanf(file, "%s", str);

			char path[256];
			strcpy(path, dir);
			strcat(path, "\\");
			strcat(path, str);
			strcat(materialArray[mc].TextureName, path);
		}
	
	}
	fclose(file);
	*MaterialArray = materialArray;
	*MaterialNum = materialNum;
}
