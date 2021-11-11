/*------------------------------------------------------------
	
	[LoadModel.cpp]
	Author : 出合翔太

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

	// 頂点バッファ生成
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
	
	// インデックスバッファ生成
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
	
	// サブセット設定
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
	// 頂点バッファ設定
	UINT stride = sizeof(Vertex3D);
	UINT offset = 0;
	m_Graphics.GetDeviceContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);

	// インデックスバッファ設定
	m_Graphics.GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	// プリミティブトポロジ設定
	m_Graphics.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	for (uint32_t i = 0; i < m_SubsetNum; i++)
	{
		// マテリアル設定
		m_Graphics.SetMaterial(m_SubsetArray[i].Material.Material);

		// テクスチャ設定
		m_Graphics.GetDeviceContext()->PSSetShaderResources(0, 1, m_SubsetArray[i].Material.Texture.GetAddressOf());

		// ポリゴン描画
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
		std::domain_error("ファイルが開けない");
	}

	//要素数カウント
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

			//四角は三角に分割
			if (in == 4)
			{
				in = 6;
			}
			indexNum += in;
		}
	}

	//メモリ確保
	positionArray = new DirectX::XMFLOAT3[positionNum];
	normalArray = new DirectX::XMFLOAT3[normalNum];
	texcoordArray = new DirectX::XMFLOAT2[texcoordNum];
	Model->VertexArray = new Vertex3D[vertexNum];
	Model->VertexNum = vertexNum;
	Model->IndexArray = new uint32_t[indexNum];
	Model->IndexNum = indexNum;
	Model->SubsetArray = new Sebset[subsetNum];
	Model->SubsetNum = subsetNum;

	//要素読込
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
			//マテリアルファイル
			fscanf(file, "%s", str);

			char path[256];
			strcpy(path, dir);
			strcat(path, "\\");
			strcat(path, str);

			LoadMaterial(path, &materialArray, &materialNum);
		}
		else if (strcmp(str, "o") == 0)
		{
			//オブジェクト名
			fscanf(file, "%s", str);
		}
		else if (strcmp(str, "v") == 0)
		{
			//頂点座標
			fscanf(file, "%f", &position->x);
			fscanf(file, "%f", &position->y);
			fscanf(file, "%f", &position->z);
			position++;
		}
		else if (strcmp(str, "vn") == 0)
		{
			//法線
			fscanf(file, "%f", &normal->x);
			fscanf(file, "%f", &normal->y);
			fscanf(file, "%f", &normal->z);
			normal++;
		}
		else if (strcmp(str, "vt") == 0)
		{
			//テクスチャ座標
			fscanf(file, "%f", &texcoord->x);
			fscanf(file, "%f", &texcoord->y);
			texcoord->y = 1.0f - texcoord->y;
			texcoord++;
		}
		else if (strcmp(str, "usemtl") == 0)
		{
			//マテリアル
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
			//面
			in = 0;
			do
			{
				fscanf(file, "%s", str);

				s = strtok(str, "/");
				Model->VertexArray[vc].Position = positionArray[atoi(s) - 1];
				if (s[strlen(s) + 1] != '/')
				{
					//テクスチャ座標が存在しない場合もある
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

			//四角は三角に分割
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
		std::domain_error("ファイルが開けない");
	}

	ModelMaterial *materialArray;
	uint32_t materialNum = 0;

	//要素数カウント
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
	//メモリ確保
	materialArray = new ModelMaterial[materialNum];

	//要素読込
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
			//マテリアル名
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
			//アンビエント
			fscanf(file, "%f", &materialArray[mc].Material.Ambient.x);
			fscanf(file, "%f", &materialArray[mc].Material.Ambient.y);
			fscanf(file, "%f", &materialArray[mc].Material.Ambient.z);
			materialArray[mc].Material.Ambient.w = 1.0f;
		}
		else if (strcmp(str, "Kd") == 0)
		{
			//ディフューズ
			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.x);
			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.y);
			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.z);
			materialArray[mc].Material.Diffuse.w = 1.0f;
		}
		else if (strcmp(str, "Ks") == 0)
		{
			//スペキュラ
			fscanf(file, "%f", &materialArray[mc].Material.Specular.x);
			fscanf(file, "%f", &materialArray[mc].Material.Specular.y);
			fscanf(file, "%f", &materialArray[mc].Material.Specular.z);
			materialArray[mc].Material.Specular.w = 1.0f;
		}
		else if (strcmp(str, "Ns") == 0)
		{
			//スペキュラ強度
			fscanf(file, "%f", &materialArray[mc].Material.Shininess);
		}
		else if (strcmp(str, "d") == 0)
		{
			//アルファ
			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.w);
		}
		else if (strcmp(str, "map_Kd") == 0)
		{
			//テクスチャ
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
