/*------------------------------------------------------------

	[Collision.h]
	Author : 出合翔太

	当たり判定を検知するクラス、関数をまとめる

-------------------------------------------------------------*/
#include "Collision.h"
#include "Application.h"
#include "Engine.h"
#include "Graphics.h"
#include "Resource.h"

// Sphere3
#pragma region class_Sphere3_method
Sphere3::Sphere3(const D3DXVECTOR3 & Position, float Radius) : m_Center(Position), m_Radius(Radius)
{
	
}

Sphere3::~Sphere3()
{
}

void Sphere3::Update(const D3DXVECTOR3 & Position)
{
	m_Center = Position;
}

void Sphere3::Update()
{
	m_oldCenter = m_Center;
}

const D3DXVECTOR3 & Sphere3::GetCenter() const
{
	return m_Center;
}
const D3DXVECTOR3 & Sphere3::GetOldCenter() const
{
	return m_oldCenter;
}
const float Sphere3::GetRadius() const
{
	return m_Radius;
}
#pragma endregion Sphere3メソッド

// AABB3
#pragma region class_AABB3_method
namespace Debug
{
	struct LineVertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DXVECTOR4 color;
	};
}

AABB3::AABB3(const D3DXVECTOR3 & Center, const D3DXVECTOR3 & Size) : m_Center(Center), m_Size(Size)
{
	m_Min = m_Center - m_Size;
	m_Max = m_Center + m_Size;
}

AABB3::~AABB3() {}

#pragma region Setting_SystemDebug
void AABB3::SystemDraw()
{
#if 0
	auto& Graphics = Engine::Get().GetGraphics();
	auto& resource = Engine::Get().GetResource();
	resource->SetShader("NoLighting");
	
	m_Min = GetMin();
	m_Max = GetMax();
	
	Debug::LineVertex v[8];
	v[0].position = D3DXVECTOR3(m_Min.x, m_Max.y, m_Min.z);
	v[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[0].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	v[1].position = D3DXVECTOR3(m_Max.x, m_Max.y, m_Min.z);
	v[1].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[1].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	v[2].position = D3DXVECTOR3(m_Min.x, m_Min.y, m_Min.z);
	v[2].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[2].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	v[3].position = D3DXVECTOR3(m_Max.x, m_Min.y, m_Min.z);
	v[3].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[3].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	v[4].position = D3DXVECTOR3(m_Min.x, m_Max.y, m_Max.z);
	v[4].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[4].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	v[5].position = D3DXVECTOR3(m_Max.x, m_Max.y, m_Max.z);
	v[5].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[5].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	v[6].position = D3DXVECTOR3(m_Min.x, m_Min.y, m_Max.z);
	v[6].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[6].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	v[7].position = D3DXVECTOR3(m_Max.x, m_Min.y, m_Max.z);
	v[7].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[7].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	
	int* index = new int[24];
	index[0] = 0;
	index[1] = 1;
	index[2] = 0;
	index[3] = 2;
	index[4] = 1;
	index[5] = 3;
	index[6] = 2;
	index[7] = 3;
	index[8] = 0;
	index[9] = 4;
	index[10] = 1;
	index[11] = 5;
	index[12] = 2;
	index[13] = 6;
	index[14] = 3;
	index[15] = 7;
	index[16] = 4;
	index[17] = 5;
	index[18] = 4;
	index[19] = 6;
	index[20] = 5;
	index[21] = 7;
	index[22] = 6;
	index[23] = 7;
	
	ID3D11Buffer* pVB = nullptr;
	ID3D11Buffer* pIB = nullptr;
	
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Debug::LineVertex) * 8;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = v;
	sd.SysMemPitch = 0;
	sd.SysMemSlicePitch = 0;
	Graphics->GetDevice()->CreateBuffer(&bd, &sd, &pVB);
	
	D3D11_BUFFER_DESC bd2;
	ZeroMemory(&bd2, sizeof(bd2));
	bd2.Usage = D3D11_USAGE_DEFAULT;
	bd2.ByteWidth = sizeof(unsigned int) * 24;
	bd2.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd2.CPUAccessFlags = 0;
	bd2.MiscFlags = 0;
	bd2.StructureByteStride = 0;
	
	D3D11_SUBRESOURCE_DATA sd2;
	ZeroMemory(&sd2, sizeof(sd2));
	sd2.pSysMem = index;
	sd2.SysMemPitch = 0;
	sd2.SysMemSlicePitch = 0;
	
	Graphics->GetDevice()->CreateBuffer(&bd2, &sd2, &pIB);
	
	D3DXMATRIX world;
	D3DXMatrixIsIdentity(&world);
	Graphics->SetWorldMatrix(world);
	
	UINT stride = sizeof(Debug::LineVertex);
	UINT offset = 0;
	Graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, &pVB, &stride, &offset);
	
	// インデックスバッファ設定
	Graphics->GetDeviceContext()->IASetIndexBuffer(pIB, DXGI_FORMAT_R32_UINT, 0);
	
	// プリミティブトポロジ設定
	Graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	
	// ポリゴン描画
	Graphics->GetDeviceContext()->DrawIndexed(24, 0, 0);	
	
	SAFE_RELEASE(pVB);
	SAFE_RELEASE(pIB);
#endif
}

void AABB3::Update(const D3DXVECTOR3 & Position)
{
	m_Center = Position;
	m_Min = m_Center - m_Size;
	m_Max = m_Center + m_Size;
}

#pragma endregion デバッグ用の設定

void AABB3::Update(const D3DXVECTOR3 & Position, const D3DXVECTOR3& Rot)
{
	m_Center = Position;
	m_Min = m_Center - m_Size;
	m_Max = m_Center + m_Size;
}

bool AABB3::Contains(const D3DXVECTOR3 & Point) const
{
	bool outside = Point.x < m_Min.x || Point.y < m_Min.y || Point.z < m_Min.z || Point.x > m_Max.x || Point.y > m_Max.y || Point.z > m_Max.z;
	// pointはBoxの中にある
	return !outside;
}

float AABB3::MinDistSq(const D3DXVECTOR3 & Position) const
{
	float dx = Math::Max(m_Min.x - Position.x, 0.0f);
	dx = Math::Max(dx, Position.x - m_Max.x);
	float dy = Math::Max(m_Min.y - Position.y, 0.0f);
	dy = Math::Max(dy, Position.y - m_Max.y);
	float dz = Math::Max(m_Min.z - Position.z, 0.0f);
	dz = Math::Max(dy, Position.z - m_Max.z);
	return dx * dx + dy * dy + dz * dz;
}

const D3DXVECTOR3& AABB3::GetMin() const
{
	return m_Min;
}

const D3DXVECTOR3& AABB3::GetMax() const
{
	return m_Max;
}

void AABB3::UpdateMinMax(const D3DXVECTOR3 & Point)
{
	m_Min.x = Math::Min(m_Min.x, Point.x);
	m_Min.y = Math::Min(m_Min.y, Point.y);
	m_Min.z = Math::Min(m_Min.z, Point.z);
	m_Max.x = Math::Max(m_Max.x, Point.x);
	m_Max.y = Math::Max(m_Max.y, Point.y);
	m_Max.z = Math::Max(m_Max.z, Point.z);
}
#pragma endregion AABB3メソッド

// OBB3
#pragma region OBB3_method
OBB3::OBB3(const Transform & Transform, const D3DXVECTOR3 & Size)
{
	auto transform = Transform;
	m_Position = transform.GetPosition();
	// 0,1,2 = x,y,z
	m_Direction[Vector::right] = transform.right();
	m_Direction[Vector::up] = transform.up();
	m_Direction[Vector::forward] = transform.forward();

	m_DirectLength[Vector::right] = Size.x;
	m_DirectLength[Vector::up] = Size.y;
	m_DirectLength[Vector::forward] = Size.z;
}

OBB3::~OBB3()
{
}

void OBB3::Update(const D3DXVECTOR3& Position, const Transform & Transform)
{
	m_Transform = Transform;
	m_Position = Position;
	// 0,1,2 = x,y,z
	m_Direction[Vector::right] = m_Transform.right();
	m_Direction[Vector::up] = m_Transform.up();
	m_Direction[Vector::forward] = m_Transform.forward();
}

void OBB3::SystemDraw()
{
#if 1
	auto& Graphics = Engine::Get().GetGraphics();
	auto& resource = Engine::Get().GetResource();
	resource->SetShader("NoLighting");

	// 端の点を求める
	D3DXVECTOR3 min, max;
	min.x = m_Position.x - m_DirectLength[Vector::right];
	min.y = m_Position.y - m_DirectLength[Vector::up];
	min.z = m_Position.z - m_DirectLength[Vector::forward];

	max.x = m_Position.x + m_DirectLength[Vector::right];
	max.y = m_Position.y + m_DirectLength[Vector::up];
	max.z = m_Position.z + m_DirectLength[Vector::forward];
	
	Debug::LineVertex v[8];
	v[0].position = D3DXVECTOR3(min.x, max.y, min.z);
	v[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[0].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	v[1].position = D3DXVECTOR3(max.x, max.y, min.z);
	v[1].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[1].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	v[2].position = D3DXVECTOR3(min.x, min.y, min.z);
	v[2].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[2].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	v[3].position = D3DXVECTOR3(max.x, min.y, min.z);
	v[3].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[3].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	v[4].position = D3DXVECTOR3(min.x, max.y, max.z);
	v[4].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[4].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	v[5].position = D3DXVECTOR3(max.x, max.y, max.z);
	v[5].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[5].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	v[6].position = D3DXVECTOR3(min.x, min.y, max.z);
	v[6].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[6].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	v[7].position = D3DXVECTOR3(max.x, min.y, max.z);
	v[7].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v[7].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	int* index = new int[24];
	index[0] = 0;
	index[1] = 1;
	index[2] = 0;
	index[3] = 2;
	index[4] = 1;
	index[5] = 3;
	index[6] = 2;
	index[7] = 3;
	index[8] = 0;
	index[9] = 4;
	index[10] = 1;
	index[11] = 5;
	index[12] = 2;
	index[13] = 6;
	index[14] = 3;
	index[15] = 7;
	index[16] = 4;
	index[17] = 5;
	index[18] = 4;
	index[19] = 6;
	index[20] = 5;
	index[21] = 7;
	index[22] = 6;
	index[23] = 7;

	ID3D11Buffer* pVB = nullptr;
	ID3D11Buffer* pIB = nullptr;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Debug::LineVertex) * 8;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = v;
	sd.SysMemPitch = 0;
	sd.SysMemSlicePitch = 0;
	Graphics->GetDevice()->CreateBuffer(&bd, &sd, &pVB);

	D3D11_BUFFER_DESC bd2;
	ZeroMemory(&bd2, sizeof(bd2));
	bd2.Usage = D3D11_USAGE_DEFAULT;
	bd2.ByteWidth = sizeof(unsigned int) * 24;
	bd2.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd2.CPUAccessFlags = 0;
	bd2.MiscFlags = 0;
	bd2.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA sd2;
	ZeroMemory(&sd2, sizeof(sd2));
	sd2.pSysMem = index;
	sd2.SysMemPitch = 0;
	sd2.SysMemSlicePitch = 0;

	Graphics->GetDevice()->CreateBuffer(&bd2, &sd2, &pIB);

	D3DXMATRIX world;

	D3DXMatrixIdentity(&world);
	Graphics->SetWorldMatrix(world);

	UINT stride = sizeof(Debug::LineVertex);
	UINT offset = 0;
	Graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, &pVB, &stride, &offset);

	// インデックスバッファ設定
	Graphics->GetDeviceContext()->IASetIndexBuffer(pIB, DXGI_FORMAT_R32_UINT, 0);

	// プリミティブトポロジ設定
	Graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// ポリゴン描画
	Graphics->GetDeviceContext()->DrawIndexed(24, 0, 0);

	SAFE_RELEASE(pVB);
	SAFE_RELEASE(pIB);
#endif
}

const D3DXVECTOR3 & OBB3::GetPosition() const
{
	return m_Position;
}

const D3DXVECTOR3 & OBB3::GetDirection(Vector Vector) const
{
	return m_Direction[Vector];
}

const float OBB3::GetLength(Vector Vector) const
{
	return m_DirectLength[Vector];
}
#pragma endregion OBB3メソッド


#pragma region Function_Intersect
// ヘルパー関数
namespace
{
	// OBB3のヘルパー関数
	// 分離軸に投影された軸成分から投影線分長を算出
	float LengthSeparateAxis(const D3DXVECTOR3& Sep, const D3DXVECTOR3& E1, const D3DXVECTOR3& E2, const D3DXVECTOR3& E3 = D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		float r1 = Math::Abs(D3DXVec3Dot(&Sep, &E1));
		float r2 = Math::Abs(D3DXVec3Dot(&Sep, &E2));
		float r3 = E3 ? Math::Abs(D3DXVec3Dot(&Sep, &E3)) : 0;
		return r1 + r2 + r3;
	}
}

bool Intersect(const Sphere3 & a, const Sphere3 & b)
{
	D3DXVECTOR3 vec = a.GetCenter() - b.GetCenter();
 	float distsq = D3DXVec3LengthSq(&vec);
	float sumRadius = a.GetRadius() + b.GetRadius();
	if(distsq <= (sumRadius * sumRadius))
	{
		return true;
	}
	return false;
}

bool Intersect(const AABB3 & a, const AABB3 & b)
{
	D3DXVECTOR3 minA, maxA, minB, maxB;
	// Aの最小点と最大点
	minA = a.GetMin();
	maxA = a.GetMax();
	// Bの最小点と最大点
	maxB = b.GetMax();
	minB = b.GetMin();
	
	//	X軸の比較
	if (maxA.x > minB.x && minA.x < maxB.x)
	{
		//	Y軸の比較
		if (maxA.y > minB.y && minA.y < maxB.y)
		{
			//	Z軸の比較
			if (maxA.z > minB.z && minA.z < maxB.z)
			{
				return true;
			}
		}
	}
	return false;
}

bool Intersect(const Sphere3 & s, const OBB3 & b)
{
	D3DXVECTOR3 dist = b.GetPosition() - s.GetCenter();
	float dot = D3DXVec3Dot(&dist, &dist);
	if (dot <= s.GetRadius() * s.GetRadius())
	{
		return true;
	}
	return false;
}

bool Intersect(const Sphere3 & s, const AABB3 & b)
{
	float distSq = b.MinDistSq(s.GetCenter());
	if(distSq <= (s.GetRadius() * s.GetRadius()))
	{
		return true;
	}
	return false;
}

bool Intersect(const AABB3 & b, const Sphere3 & s)
{
	float distSq = b.MinDistSq(s.GetCenter());
	if (distSq <= (s.GetRadius() * s.GetRadius()))
	{
		return true;
	}
	return false;
}

bool Intersect(const OBB3 & a, const OBB3 & b)
{
	OBB3 obj_a = a;
	OBB3 obj_b = b;
	D3DXVECTOR3 Nae1 = obj_a.GetDirection(OBB3::Vector::right);
	D3DXVECTOR3 ae1 = Nae1 * obj_a.GetLength(OBB3::Vector::right);
	D3DXVECTOR3 Nae2 = obj_a.GetDirection(OBB3::Vector::up);
	D3DXVECTOR3 ae2 = Nae2 * obj_a.GetLength(OBB3::Vector::up);
	D3DXVECTOR3 Nae3 = obj_a.GetDirection(OBB3::Vector::forward);
	D3DXVECTOR3 ae3 = Nae3 * obj_a.GetLength(OBB3::Vector::forward);

	D3DXVECTOR3 Nbe1 = obj_b.GetDirection(OBB3::Vector::right);
	D3DXVECTOR3 be1 = Nae1 * obj_b.GetLength(OBB3::Vector::right);
	D3DXVECTOR3 Nbe2 = obj_b.GetDirection(OBB3::Vector::up);
	D3DXVECTOR3 be2 = Nae2 * obj_b.GetLength(OBB3::Vector::up);
	D3DXVECTOR3 Nbe3 = obj_b.GetDirection(OBB3::Vector::forward);
	D3DXVECTOR3 be3 = Nae3 * obj_b.GetLength(OBB3::Vector::forward);

	D3DXVECTOR3 Interval = obj_a.GetPosition() - obj_b.GetPosition();

	// 分離軸 : ae1
	float rA = D3DXVec3Length(&ae1);
	float rB = LengthSeparateAxis(Nae1, be1, be2, be3);
	float L = Math::Abs(D3DXVec3Dot(&Interval, &Nae1));
	if (L > rA + rB)
	{
		return false;
	}
	 // 分離軸 : ae2
	rA = D3DXVec3Length(&ae2);
	rB = LengthSeparateAxis(Nae2, be1, be2, be3);
	L = Math::Abs(D3DXVec3Dot(&Interval, &Nae2));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : ae3
	rA = D3DXVec3Length(&ae3);
	rB = LengthSeparateAxis(Nae3, be1, be2, be3);
	L = Math::Abs(D3DXVec3Dot(&Interval, &Nae3));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : be1
	rA = LengthSeparateAxis(Nbe1, ae1, ae2, ae3);
	rB = D3DXVec3Length(&be1);
	L = Math::Abs(D3DXVec3Dot(&Interval, &Nbe1));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : be2
	rA = LengthSeparateAxis(Nbe2, ae1, ae2, ae3);
	rB = D3DXVec3Length(&be2);
	L = Math::Abs(D3DXVec3Dot(&Interval, &Nbe2));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : be3
	rA = LengthSeparateAxis(Nbe3, ae1, ae2, ae3);
	rB = D3DXVec3Length(&be3);
	L = Math::Abs(D3DXVec3Dot(&Interval, &Nbe3));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C11
	D3DXVECTOR3 cross;
	D3DXVec3Cross(&cross, &Nae1, &Nbe1);
	rA = LengthSeparateAxis(cross, ae2, ae3);
	rB = LengthSeparateAxis(cross, be2, be3);
	L = Math::Abs(D3DXVec3Dot(&Interval, &cross));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : C12
	D3DXVec3Cross(&cross, &Nae1, &Nbe2);
	rA = LengthSeparateAxis(cross, ae2, ae3);
	rB = LengthSeparateAxis(cross, be1, be3);
	L = Math::Abs(D3DXVec3Dot(&Interval, &cross));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : C13
	D3DXVec3Cross(&cross, &Nae1, &Nbe3);
	rA = LengthSeparateAxis(cross, ae2, ae3);
	rB = LengthSeparateAxis(cross, be1, be2);
	L = Math::Abs(D3DXVec3Dot(&Interval, &cross));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : C21
	D3DXVec3Cross(&cross, &Nae2, &Nbe1);
	rA = LengthSeparateAxis(cross, ae1, ae3);
	rB = LengthSeparateAxis(cross, be2, be3);
	L = Math::Abs(D3DXVec3Dot(&Interval, &cross));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : C22
	D3DXVec3Cross(&cross, &Nae2, &Nbe2);
	rA = LengthSeparateAxis(cross, ae1, ae3);
	rB = LengthSeparateAxis(cross, be1, be3);
	L = Math::Abs(D3DXVec3Dot(&Interval, &cross));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : C23
	D3DXVec3Cross(&cross, &Nae2, &Nbe3);
	rA = LengthSeparateAxis(cross, ae1, ae3);
	rB = LengthSeparateAxis(cross, be1, be2);
	L = Math::Abs(D3DXVec3Dot(&Interval, &cross));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : C31
	D3DXVec3Cross(&cross, &Nae3, &Nbe1);
	rA = LengthSeparateAxis(cross, ae1, ae2);
	rB = LengthSeparateAxis(cross, be2, be3);
	L = Math::Abs(D3DXVec3Dot(&Interval, &cross));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : C32
	D3DXVec3Cross(&cross, &Nae3, &Nbe2);
	rA = LengthSeparateAxis(cross, ae1, ae2);
	rB = LengthSeparateAxis(cross, be1, be3);
	L = Math::Abs(D3DXVec3Dot(&Interval, &cross));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : C33
	D3DXVec3Cross(&cross, &Nae3, &Nbe3);
	rA = LengthSeparateAxis(cross, ae1, ae2);
	rB = LengthSeparateAxis(cross, be1, be2);
	L = Math::Abs(D3DXVec3Dot(&Interval, &cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離平面が存在->衝突している
	return true;
}

// 連続衝突検知
bool CCD(const Sphere3 & p, const Sphere3 & q, float & t)
{
	D3DXVECTOR3 x = p.GetOldCenter() - q.GetOldCenter();
	D3DXVECTOR3 y = p.GetCenter() - p.GetOldCenter() - (q.GetCenter() - q.GetOldCenter());
	float a = D3DXVec3Dot(&y, &y);
	float b = 2.0f * D3DXVec3Dot(&x, &y);
	float sumRadius = p.GetRadius() + q.GetRadius();
	float c = D3DXVec3Dot(&x, &x) - sumRadius * sumRadius;
	// 判別式
	float dist = b * b - 4.0f * a * c;
	if (dist < 0.0f)
	{
		return false;
	}
	else
	{
		dist = Math::Sqrt(dist);
		// 小さいのほうの解
		t = (-b - dist) / (2.0f * a);
		if (t >= 0.0f && t <= 0.0f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}
#pragma endregion 当たったかどうか検知する関数