/*-------------------------------------------------------------

	[Supply.cpp]
	Author : 出合翔太

	補給地点

--------------------------------------------------------------*/
#include "Engine.h"
#include "Application.h"
#include "Graphics.h"
#include "Resource.h"
#include "Supply.h"
#include "GameCamera.h"

#pragma region パーティクル
CircleParticle::CircleParticle() : m_Resource(*Engine::Get().resource()), m_Graphics(*Engine::Get().graphics())
{
	// 頂点作成
	Vertex3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-0.1f, 0.1f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(0.1f, 0.1f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-0.1f, -0.1f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(0.1f, -0.1f, 0.0f);
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

	m_Transform = AddComponent<Transform>();
	m_Transform->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 5.0f));
	m_Color = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
}

CircleParticle::~CircleParticle()
{
}

void CircleParticle::Begin()
{

}

void CircleParticle::Update()
{

}

void CircleParticle::Event()
{
}

void CircleParticle::Draw()
{
	m_Graphics.SetAlphaToCoverageEnable(true);

	// ライティングなし
	m_Resource.SetShader("NoLighting");

	// ブレンドステートは加算
	m_Graphics.SetBlendStateAdd();

	// マトリクスの設定
	auto camera = Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	D3DXMATRIX view = camera->view();

	// ビューの逆行列
	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view);//逆行列
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;
	
	// 座標変換
	D3DXMATRIX world, scale, rot, trans;
	Math::Matrix::MatrixScaling(&scale, transform().scale());
	Math::Matrix::MatrixTranslation(&trans, transform().position());
	world = scale * invView * trans;
	m_Graphics.SetWorldMatrix(world);

	m_Resource.SetTexture(0, "Effect");

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
	m_Graphics.SetAlphaToCoverageEnable(false);
}

void CircleParticle::Generate(float x, float z)
{
	m_Transform->position().x = x;
	m_Transform->position().y = .0f;
	m_Transform->position().z = z;
}
#pragma endregion パーティクル

Supply::Supply()
{
	m_Transform = AddComponent<Transform>();
	m_Collider = AddComponent<Collider>();
	m_Angle = 0;
	m_Radius = 30.0f;
}

Supply::~Supply()
{
}

void Supply::Begin()
{	
	D3DXVECTOR3 size = D3DXVECTOR3(10.0f, 3.0, 7.0f);
	m_Collider->SetSphere3(*m_Transform, m_Radius);
	m_Collider->SetOBB3(*m_Transform, size);
	
	for (int i = 0; i < 120; i++)
	{
		m_Particles.emplace_back(Engine::Get().application()->GetScene()->AddGameObject<CircleParticle>(ELayer::LAYER_2D_EFFECT));

		float radius = m_Angle * 3.14f / 180.0f;

		// 三角関数を使用し、円の位置を割り出す。
		float add_x = cos(radius) * m_Radius;
		float add_z = sin(radius) * m_Radius;

		// 結果ででた位置を中心位置に加算し、それを描画位置とする
		float x = m_Transform->position().x + add_x;
		float z = m_Transform->position().z + add_z;

		m_Particles[i]->Generate(x, z);
		m_Angle += 3.0f;
	}
}

void Supply::Update()
{
	auto colliderPosition = m_Transform->position();
	colliderPosition.y = m_Transform->position().y + 2.0f;
	m_Collider->Update(colliderPosition, *m_Transform);
}

void Supply::Event()
{
}

void Supply::Draw()
{	
	resource().SetShader("Default");
	UpdateMatrix(*m_Transform);
	resource().SetStaticModel("Supply");
}
