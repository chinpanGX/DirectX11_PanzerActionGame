/*--------------------------------------------------------------

	[SkillParticle.cpp]
	スキル用のパーティクル
	Author : 出合翔太

---------------------------------------------------------------*/
#include "Engine.h"
#include "Graphics.h"
#include "Resource.h"
#include "SkillParticle.h"

SkillParticle::SkillParticle() : m_Resource(*Engine::Get().GetResource()), m_Graphics(*Engine::Get().GetGraphics())
{
	// 頂点作成
	Vertex3D vertex[4];

	vertex[0].Position = DirectX::XMFLOAT3(-1.0f, 0.01f, 1.0f);
	vertex[0].Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = DirectX::XMFLOAT3(1.0f, 0.01f, 1.0f);
	vertex[1].Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = DirectX::XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = DirectX::XMFLOAT3(-1.0f, 0.01f, -1.0f);
	vertex[2].Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = DirectX::XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = DirectX::XMFLOAT3(1.0f, 0.01f, -1.0f);
	vertex[3].Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = DirectX::XMFLOAT2(1.0f, 1.0f);

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

	m_Transform = Actor::AddComponent<Transform>();
}

SkillParticle::~SkillParticle()
{
}

void SkillParticle::Begin()
{
	m_Transform->Begin();
}

void SkillParticle::Update()
{
}

void SkillParticle::Event()
{
}

void SkillParticle::Draw()
{
	if (m_Life != 0)
	{
		// ライティングなし
		m_Resource.SetShader("Defualt");
		Actor::UpdateMatrix(*m_Transform);

		m_Resource.SetTexture(0, "Effect");

		// ブレンドステートは減算
		m_Graphics.SetBlendStateSub();

		// 頂点バッファ
		UINT stride = sizeof(Vertex3D);
		UINT offset = 0;
		m_Graphics.GetDeviceContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);

		//プリミティブトポロジ設定
		m_Graphics.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//ポリゴン描画
		m_Graphics.GetDeviceContext()->Draw(4, 0);

		// ブレンドステートを元に戻す
		m_Graphics.SetBlendStateDefault();
	}
}

void SkillParticle::Create(unsigned int life, Math::Vector3 position, Math::Vector4 color)
{
}
