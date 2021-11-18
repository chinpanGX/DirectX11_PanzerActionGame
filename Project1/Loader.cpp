/*-------------------------------------------------------------

	[Loader.cpp]
	Author : �o���đ�

	���\�[�X�t�@�C���̓ǂݍ��ݏ������܂Ƃ߂�

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
	positionArray = new D3DXVECTOR3[positionNum];
	normalArray = new D3DXVECTOR3[normalNum];
	texcoordArray = new D3DXVECTOR2[texcoordNum];
	Model->VertexArray = new Vertex3D[vertexNum];
	Model->VertexNum = vertexNum;
	Model->IndexArray = new uint32_t[indexNum];
	Model->IndexNum = indexNum;
	Model->SubsetArray = new Sebset[subsetNum];
	Model->SubsetNum = subsetNum;

	//�v�f�Ǎ�
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

				Model->VertexArray[vc].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

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
#pragma endregion _Obj�t�@�C���̓ǂݍ���_

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

	// ���̓��C�A�E�g����
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
#pragma endregion _VertexShader�̓ǂݍ���_

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
#pragma endregion _PixelShader�̓ǂݍ���_

#pragma region _LoadAudio_
LoadAudio::LoadAudio()
{

}

LoadAudio::~LoadAudio()
{

}

void LoadAudio::Load(const std::string & name, bool loop, IXAudio2* xaudio2)
{
	// �T�E���h�t�@�C���̓o�^
	m_Filename = name;
	m_Loop = loop;

	HRESULT hr = S_OK;;
	HANDLE hFile;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̃N���A
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// �T�E���h�f�[�^�t�@�C���̐���
	hFile = CreateFile(m_Filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		ThrowIfFailed(hr, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s(1)");
		return;
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		ThrowIfFailed(hr, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s(2)");
		return;
	}

	// WAVE�t�@�C���̃`�F�b�N
	hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)");
		return;
	}
	hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)");
		return;
	}
	if (dwFiletype != 'EVAW')
	{
		ThrowIfFailed(hr, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)");
		return;
	}

	// �t�H�[�}�b�g�`�F�b�N
	hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)");
		return;
	}
	hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)");
		return;
	}

	// �I�[�f�B�I�f�[�^�ǂݍ���
	hr = CheckChunk(hFile, 'atad', &m_sizeAudio, &dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)");
		return;
	}
	m_dataAudio = (BYTE*)malloc(m_sizeAudio);
	hr = ReadChunkData(hFile, m_dataAudio, m_sizeAudio, dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)");
		return;
	}

	// �\�[�X�{�C�X�̐���
	hr = xaudio2->CreateSourceVoice(&m_sourceVoice, &(wfx.Format));
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "�\�[�X�{�C�X�̐����Ɏ��s�I");
		return;
	}

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_sizeAudio;
	buffer.pAudioData = m_dataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	m_Loop ? buffer.LoopCount = -1 : buffer.LoopCount = 0;

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_sourceVoice->SubmitSourceBuffer(&buffer);
}

void LoadAudio::Unload()
{
	if (m_sourceVoice)
	{
		// �ꎞ��~
		m_sourceVoice->Stop(0);

		// �\�[�X�{�C�X�̔j��
		m_sourceVoice->DestroyVoice();
		m_sourceVoice = NULL;

		// �I�[�f�B�I�f�[�^�̊J��
		free(m_dataAudio);
		m_dataAudio = NULL;
	}
}

void LoadAudio::Play()
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_sizeAudio;
	buffer.pAudioData = m_dataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	m_Loop ? buffer.LoopCount = -1 : buffer.LoopCount = 0;

	// ��Ԏ擾
	m_sourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
	 // �ꎞ��~
		m_sourceVoice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_sourceVoice->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_sourceVoice->SubmitSourceBuffer(&buffer);

	// �Đ�
	m_sourceVoice->Start(0);
}

void LoadAudio::Stop()
{
	if (m_sourceVoice)
	{
		// �ꎞ��~
		m_sourceVoice->Stop(0);
	}
}

void LoadAudio::SetVolume(float volume)
{
	// �{�����[����1.0f���傫���Ȃ�Ȃ��悤�ɂ���
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
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
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
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}
	return S_OK;
}
#pragma endregion _xAudio�̓ǂݍ���_