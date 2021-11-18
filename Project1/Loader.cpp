/*-------------------------------------------------------------

	[Loader.cpp]
	Author : 出合翔太

	リソースファイルの読み込み処理をまとめる

--------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include "Engine.h"
#include "Loader.h"
#include "Utility.h"
#include <io.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#pragma region _Model_
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

	D3DXVECTOR3	*positionArray;
	D3DXVECTOR3	*normalArray;
	D3DXVECTOR2	*texcoordArray;

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
	positionArray = new D3DXVECTOR3[positionNum];
	normalArray = new D3DXVECTOR3[normalNum];
	texcoordArray = new D3DXVECTOR2[texcoordNum];
	Model->VertexArray = new Vertex3D[vertexNum];
	Model->VertexNum = vertexNum;
	Model->IndexArray = new uint32_t[indexNum];
	Model->IndexNum = indexNum;
	Model->SubsetArray = new Sebset[subsetNum];
	Model->SubsetNum = subsetNum;

	//要素読込
	D3DXVECTOR3 *position = positionArray;
	D3DXVECTOR3 *normal = normalArray;
	D3DXVECTOR2 *texcoord = texcoordArray;

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

				Model->VertexArray[vc].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

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
#pragma endregion _Objファイルの読み込み_

#pragma region _VertexShader_
LoadVertexShader::LoadVertexShader(Graphics & graphics) : m_Graphics(graphics), m_VertexShader(nullptr), m_InputLayout(nullptr)
{

}

LoadVertexShader::~LoadVertexShader()
{

}

void LoadVertexShader::Load(const std::string& name)
{
	FILE* file;
	long int fsize;
	file = fopen(name.c_str(), "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);
	auto hr = m_Graphics.GetDevice()->CreateVertexShader(buffer, fsize, nullptr, m_VertexShader.GetAddressOf());
	ThrowIfFailed(hr, "CreateVertexShader Failed");

	// 入力レイアウト生成
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);
	hr = m_Graphics.GetDevice()->CreateInputLayout(layout, numElements, buffer, fsize, m_InputLayout.GetAddressOf());
	ThrowIfFailed(hr, "CreateInputLayout Failed");
	delete[] buffer;
}

Microsoft::WRL::ComPtr<ID3D11VertexShader> LoadVertexShader::GetVertexShader() const
{
	return m_VertexShader;
}

Microsoft::WRL::ComPtr<ID3D11InputLayout> LoadVertexShader::GetInputLayout() const
{
	return m_InputLayout;
}
#pragma endregion _VertexShaderの読み込み_

#pragma region _PixelShader_
LoadPixelShader::LoadPixelShader(Graphics & graphics) : m_Graphics(graphics), m_PixelShader(nullptr)
{
}

LoadPixelShader::~LoadPixelShader()
{

}

void LoadPixelShader::Load(const std::string& name)
{
	FILE* file;
	long int fsize;
	file = fopen(name.c_str(), "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);
	auto hr = m_Graphics.GetDevice()->CreatePixelShader(buffer, fsize, nullptr, m_PixelShader.GetAddressOf());
	ThrowIfFailed(hr, "CreatePixelShader Failed");
	delete[] buffer;
}

Microsoft::WRL::ComPtr<ID3D11PixelShader> LoadPixelShader::GetPixelShader() const
{
	return m_PixelShader;
}
#pragma endregion _PixelShaderの読み込み_

#pragma region _LoadAudio_
LoadAudio::LoadAudio()
{

}

LoadAudio::~LoadAudio()
{

}

void LoadAudio::Load(const std::string & name, bool loop, IXAudio2* xaudio2)
{
	// サウンドファイルの登録
	m_Filename = name;
	m_Loop = loop;

	HRESULT hr = S_OK;;
	HANDLE hFile;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	// バッファのクリア
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// サウンドデータファイルの生成
	hFile = CreateFile(m_Filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		ThrowIfFailed(hr, "サウンドデータファイルの生成に失敗(1)");
		return;
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		ThrowIfFailed(hr, "サウンドデータファイルの生成に失敗(2)");
		return;
	}

	// WAVEファイルのチェック
	hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "WAVEファイルのチェックに失敗！(1)");
		return;
	}
	hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "WAVEファイルのチェックに失敗！(2)");
		return;
	}
	if (dwFiletype != 'EVAW')
	{
		ThrowIfFailed(hr, "WAVEファイルのチェックに失敗！(3)");
		return;
	}

	// フォーマットチェック
	hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "フォーマットチェックに失敗！(1)");
		return;
	}
	hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "フォーマットチェックに失敗！(2)");
		return;
	}

	// オーディオデータ読み込み
	hr = CheckChunk(hFile, 'atad', &m_sizeAudio, &dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "オーディオデータ読み込みに失敗！(1)");
		return;
	}
	m_dataAudio = (BYTE*)malloc(m_sizeAudio);
	hr = ReadChunkData(hFile, m_dataAudio, m_sizeAudio, dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "オーディオデータ読み込みに失敗！(2)");
		return;
	}

	// ソースボイスの生成
	hr = xaudio2->CreateSourceVoice(&m_sourceVoice, &(wfx.Format));
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "ソースボイスの生成に失敗！");
		return;
	}

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_sizeAudio;
	buffer.pAudioData = m_dataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	m_Loop ? buffer.LoopCount = -1 : buffer.LoopCount = 0;

	// オーディオバッファの登録
	m_sourceVoice->SubmitSourceBuffer(&buffer);
}

void LoadAudio::Unload()
{
	if (m_sourceVoice)
	{
		// 一時停止
		m_sourceVoice->Stop(0);

		// ソースボイスの破棄
		m_sourceVoice->DestroyVoice();
		m_sourceVoice = NULL;

		// オーディオデータの開放
		free(m_dataAudio);
		m_dataAudio = NULL;
	}
}

void LoadAudio::Play()
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_sizeAudio;
	buffer.pAudioData = m_dataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	m_Loop ? buffer.LoopCount = -1 : buffer.LoopCount = 0;

	// 状態取得
	m_sourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
	 // 一時停止
		m_sourceVoice->Stop(0);

		// オーディオバッファの削除
		m_sourceVoice->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	m_sourceVoice->SubmitSourceBuffer(&buffer);

	// 再生
	m_sourceVoice->Start(0);
}

void LoadAudio::Stop()
{
	if (m_sourceVoice)
	{
		// 一時停止
		m_sourceVoice->Stop(0);
	}
}

void LoadAudio::SetVolume(float volume)
{
	// ボリュームが1.0fより大きくならないようにする
	float v = Math::Min(volume, 1.0f);
	m_sourceVoice->SetVolume(v);
}

HRESULT LoadAudio::CheckChunk(HANDLE hFile, DWORD format, DWORD * pChunkSize, DWORD * pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

HRESULT LoadAudio::ReadChunkData(HANDLE hFile, void * pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}
	return S_OK;
}
#pragma endregion _xAudioの読み込み_