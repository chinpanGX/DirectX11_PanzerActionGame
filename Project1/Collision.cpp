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

#pragma region Line_method
Line::Line(const Math::Vector3 start, const Math::Vector3 end) : m_Start(start), m_End(end)
{
}

void Line::Update(const Math::Vector3 & pos, const Math::Vector3& vec, float distance)
{
	Math::Vector3 dir = Math::Vector3::Normalize(vec);
	m_Start = pos;
	m_End = dir * distance;
}

Math::Vector3 Line::PointOnSegment(float t) const
{
	return m_Start + (m_End - m_Start) * t;
}

float Line::MinDistSq(const Math::Vector3 & point) const
{
	// Construct vectors
	Math::Vector3 ab = m_End - m_Start;
	Math::Vector3 ba = -1.0f * ab;
	Math::Vector3 ac = point - m_Start;
	Math::Vector3 bc = point - m_End;

	// Case 1: C projects prior to A
	if (Math::Vector3::Dot(ab, ac) < 0.0f)
	{
		return ac.LengthSq();
	}
	// Case 2: C projects after B
	else if (Math::Vector3::Dot(ba, bc) < 0.0f)
	{
		return bc.LengthSq();
	}
	// Case 3: C projects onto line
	else
	{
		// Compute p
		float scalar = Math::Vector3::Dot(ac, ab) / Math::Vector3::Dot(ab, ab);
		Math::Vector3 p = scalar * ab;
		// Compute length squared of ac - p
		return (ac - p).LengthSq();
	}
}

float Line::MinDistSq(const Line & s1, const Line & s2)
{
	Math::Vector3   u = s1.m_End - s1.m_Start;
	Math::Vector3   v = s2.m_End - s2.m_Start;
	Math::Vector3   w = s1.m_Start - s2.m_Start;
	float    a = Math::Vector3::Dot(u, u);         // always >= 0
	float    b = Math::Vector3::Dot(u, v);
	float    c = Math::Vector3::Dot(v, v);         // always >= 0
	float    d = Math::Vector3::Dot(u, w);
	float    e = Math::Vector3::Dot(v, w);
	float    D = a * c - b * b;        // always >= 0
	float    sc, sN, sD = D;       // sc = sN / sD, default sD = D >= 0
	float    tc, tN, tD = D;       // tc = tN / tD, default tD = D >= 0

								   // compute the line parameters of the two closest points
	if (Math::NearZero(D)) 
	{ // the lines are almost parallel
		sN = 0.0;         // force using point P0 on segment S1
		sD = 1.0;         // to prevent possible division by 0.0 later
		tN = e;
		tD = c;
	}
	else
	{                 // get the closest points on the infinite lines
		sN = (b*e - c * d);
		tN = (a*e - b * d);
		if (sN < 0.0) 
		{        // sc < 0 => the s=0 edge is visible
			sN = 0.0;
			tN = e;
			tD = c;
		}
		else if (sN > sD) 
		{  // sc > 1  => the s=1 edge is visible
			sN = sD;
			tN = e + b;
			tD = c;
		}
	}

	if (tN < 0.0) 
	{            // tc < 0 => the t=0 edge is visible
		tN = 0.0;
		// recompute sc for this edge
		if (-d < 0.0)
		{
			sN = 0.0;
		}
		else if (-d > a)
		{
			sN = sD;
		}
		else 
		{
			sN = -d;
			sD = a;
		}
	}
	else if (tN > tD) 
	{      // tc > 1  => the t=1 edge is visible
		tN = tD;
		// recompute sc for this edge
		if ((-d + b) < 0.0)
		{
			sN = 0;
		}
		else if ((-d + b) > a)
		{
			sN = sD;
		}
		else 
		{
			sN = (-d + b);
			sD = a;
		}
	}
	// finally do the division to get sc and tc
	sc = (Math::NearZero(sN) ? 0.0f : sN / sD);
	tc = (Math::NearZero(tN) ? 0.0f : tN / tD);

	// get the difference of the two closest points
	Math::Vector3 dP = w + (sc * u) - (tc * v);  // =  S1(sc) - S2(tc)

	return dP.LengthSq();   // return the closest distance squared
}

const Math::Vector3 & Line::GetStart() const
{
	return m_Start;
}

const Math::Vector3 & Line::GetEnd() const
{
	return m_End;
}
#pragma endregion Line_method

// Plane
#pragma region class_Plane3_method
Plane3::Plane3(const Math::Vector3 & a, const Math::Vector3 & b, const Math::Vector3 & c)
{
	//　ベクトル計算
	Math::Vector3 vab = b - a;
	Math::Vector3 vac = c - a;
	// 外積と正規化で法線をだす
	m_Normal = Math::Vector3::Cross(vab, vac);
	m_Normal.Normalize();
	m_Distance = -Math::Vector3::Dot(a, m_Normal);
}
#pragma endregion Plane3メソッド

// Sphere3
#pragma region class_Sphere3_method
Sphere3::Sphere3(const Math::Vector3 & Position, float Radius) : m_Center(Position), m_Radius(Radius)
{
	
}

Sphere3::~Sphere3()
{
}

void Sphere3::Update(const Math::Vector3 & Position)
{
	m_Center = Position;
}

void Sphere3::Update()
{
	m_oldCenter = m_Center;
}

const Math::Vector3 & Sphere3::GetCenter() const
{
	return m_Center;
}
const Math::Vector3 & Sphere3::GetOldCenter() const
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
		Math::Vector3 position;
		Math::Vector3 normal;
		Math::Vector4 color;
	};
}

AABB3::AABB3(const Math::Vector3 & Center, const Math::Vector3 & Size) : m_Center(Center), m_Size(Size)
{
	m_Min = m_Center - m_Size;
	m_Max = m_Center + m_Size;
}

AABB3::~AABB3() {}

#pragma region Setting_SystemDebug
void AABB3::SystemDraw()
{
#if 1
	auto& graphics = Engine::Get().GetGraphics();
	auto& resource = Engine::Get().GetResource();
	resource->SetShader("NoLighting");
	
	m_Min = GetMin();
	m_Max = GetMax();
	
	Debug::LineVertex v[8];
	v[0].position = Math::Vector3(m_Min.x, m_Max.y, m_Min.z);
	v[0].normal = Math::Vector3(0.0f, 1.0f, 0.0f);
	v[0].color = Math::Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	v[1].position = Math::Vector3(m_Max.x, m_Max.y, m_Min.z);
	v[1].normal = Math::Vector3(0.0f, 1.0f, 0.0f);
	v[1].color = Math::Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	v[2].position = Math::Vector3(m_Min.x, m_Min.y, m_Min.z);
	v[2].normal = Math::Vector3(0.0f, 1.0f, 0.0f);
	v[2].color = Math::Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	v[3].position = Math::Vector3(m_Max.x, m_Min.y, m_Min.z);
	v[3].normal = Math::Vector3(0.0f, 1.0f, 0.0f);
	v[3].color = Math::Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	v[4].position = Math::Vector3(m_Min.x, m_Max.y, m_Max.z);
	v[4].normal = Math::Vector3(0.0f, 1.0f, 0.0f);
	v[4].color = Math::Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	v[5].position = Math::Vector3(m_Max.x, m_Max.y, m_Max.z);
	v[5].normal = Math::Vector3(0.0f, 1.0f, 0.0f);
	v[5].color = Math::Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	v[6].position = Math::Vector3(m_Min.x, m_Min.y, m_Max.z);
	v[6].normal = Math::Vector3(0.0f, 1.0f, 0.0f);
	v[6].color = Math::Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	v[7].position = Math::Vector3(m_Max.x, m_Min.y, m_Max.z);
	v[7].normal = Math::Vector3(0.0f, 1.0f, 0.0f);
	v[7].color = Math::Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	
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
	graphics->GetDevice()->CreateBuffer(&bd, &sd, &pVB);
	
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
	
	graphics->GetDevice()->CreateBuffer(&bd2, &sd2, &pIB);
	
	DirectX::XMMATRIX world;
	world = DirectX::XMMatrixIdentity();
	graphics->SetWorldMatrix(world);
	
	UINT stride = sizeof(Debug::LineVertex);
	UINT offset = 0;
	graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, &pVB, &stride, &offset);
	
	// インデックスバッファ設定
	graphics->GetDeviceContext()->IASetIndexBuffer(pIB, DXGI_FORMAT_R32_UINT, 0);
	
	// プリミティブトポロジ設定
	graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	
	// ポリゴン描画
	graphics->GetDeviceContext()->DrawIndexed(24, 0, 0);	
	
	SAFE_RELEASE(pVB);
	SAFE_RELEASE(pIB);
#endif
}

void AABB3::Update(const Math::Vector3 & Position)
{
	m_Center = Position;
	m_Min = m_Center - m_Size;
	m_Max = m_Center + m_Size;
}

#pragma endregion デバッグ用の設定

void AABB3::Update(const Math::Vector3 & Position, const Math::Quaternion& Rot)
{
	m_Center = Position;
	m_Min = m_Center - m_Size;
	m_Max = m_Center + m_Size;
	UpdateRotate(Rot);
}

bool AABB3::Contains(const Math::Vector3 & point) const
{
	bool outside = point.x < m_Min.x || point.y < m_Min.y || point.z < m_Min.z || point.x > m_Max.x || point.y > m_Max.y || point.z > m_Max.z;
	// pointはBoxの中にある
	return !outside;
}

float AABB3::MinDistSq(const Math::Vector3 & Position) const
{
	float dx = Math::Max(m_Min.x - Position.x, 0.0f);
	dx = Math::Max(dx, Position.x - m_Max.x);
	float dy = Math::Max(m_Min.y - Position.y, 0.0f);
	dy = Math::Max(dy, Position.y - m_Max.y);
	float dz = Math::Max(m_Min.z - Position.z, 0.0f);
	dz = Math::Max(dy, Position.z - m_Max.z);
	return dx * dx + dy * dy + dz * dz;
}

const Math::Vector3& AABB3::GetMin() const
{
	return m_Min;
}

const Math::Vector3& AABB3::GetMax() const
{
	return m_Max;
}
void AABB3::UpdateRotate(const Math::Quaternion & Rot)
{
	m_Min = m_Center - m_Size;
	m_Max = m_Center + m_Size;
	std::array<Math::Vector3, 8> points;
	points[0] = m_Min;
	points[1] = Math::Vector3(m_Max.x, m_Min.y, m_Min.z);
	points[2] = Math::Vector3(m_Min.x, m_Max.y, m_Min.z);
	points[3] = Math::Vector3(m_Min.x, m_Min.y, m_Max.z);
	points[4] = Math::Vector3(m_Min.x, m_Max.y, m_Max.z);
	points[5] = Math::Vector3(m_Max.x, m_Min.y, m_Max.z);
	points[6] = Math::Vector3(m_Max.x, m_Max.y, m_Min.z);
	points[7] = Math::Vector3(m_Max);

	//　点をリセット
	Math::Vector3 p = Math::Vector3::Transform(points[0], Rot);
	m_Min = p;
	m_Max = p;
	// 回転した点からBoxの大きさを更新
	for (size_t i = 1; i < points.size(); i++)
	{
		p = Math::Vector3::Transform(points[i], Rot);
		UpdateMinMax(p);
	}
}

void AABB3::UpdateMinMax(const Math::Vector3 & Point)
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
OBB3::OBB3(const Transform & t, const Math::Vector3 & Size)
{
	auto transform = t;
	m_Position = transform.position();
	m_Size = Size;

	// 0,1,2 = x,y,z
	m_Dir[0] = transform.GetVector(Transform::Vector::Right);
	m_Dir[1] = transform.GetVector(Transform::Vector::Up);
	m_Dir[2] = transform.GetVector(Transform::Vector::Forward);

	m_Min = m_Position - m_Size;
	m_Max = m_Position + m_Size;
	m_Length.x = Math::Abs(m_Max.x - m_Min.x) * 0.5f;
	m_Length.y = Math::Abs(m_Max.y - m_Min.y) * 0.5f;
	m_Length.z = Math::Abs(m_Max.z - m_Min.z) * 0.5f;
}

OBB3::~OBB3()
{
}

void OBB3::Update(const Math::Vector3& Position, const Transform & t)
{
	auto transform = t;
	m_Position = Position;
	// 0,1,2 = x,y,z
	m_Dir[0] = transform.GetVector(Transform::Vector::Right);
	m_Dir[1] = transform.GetVector(Transform::Vector::Up);
	m_Dir[2] = transform.GetVector(Transform::Vector::Forward);
	m_Min = m_Position - m_Size;
	m_Max = m_Position + m_Size;
	m_Length.x = Math::Abs(m_Max.x - m_Min.x) * 0.5f;
	m_Length.y = Math::Abs(m_Max.y - m_Min.y) * 0.5f;
	m_Length.z = Math::Abs(m_Max.z - m_Min.z) * 0.5f;
}

void OBB3::SystemDraw()
{
#if 1
	auto& graphics = Engine::Get().GetGraphics();
	auto& resource = Engine::Get().GetResource();
	resource->SetShader("NoLighting");

	// 端の点を求める
	m_Min = m_Position - m_Size;
	m_Max = m_Position + m_Size;
	
	Debug::LineVertex v[8];
	v[0].position = Math::Vector3(m_Min.x, m_Max.y, m_Min.z);
	v[0].normal = Math::Vector3(0.0f, 1.0f, 0.0f);
	v[0].color = Math::Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	v[1].position = Math::Vector3(m_Max.x, m_Max.y, m_Min.z);
	v[1].normal = Math::Vector3(0.0f, 1.0f, 0.0f);
	v[1].color = Math::Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	v[2].position = Math::Vector3(m_Min.x, m_Min.y, m_Min.z);
	v[2].normal = Math::Vector3(0.0f, 1.0f, 0.0f);
	v[2].color = Math::Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	v[3].position = Math::Vector3(m_Max.x, m_Min.y, m_Min.z);
	v[3].normal = Math::Vector3(0.0f, 1.0f, 0.0f);
	v[3].color = Math::Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	v[4].position = Math::Vector3(m_Min.x, m_Max.y, m_Max.z);
	v[4].normal = Math::Vector3(0.0f, 1.0f, 0.0f);
	v[4].color = Math::Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	v[5].position = Math::Vector3(m_Max.x, m_Max.y, m_Max.z);
	v[5].normal = Math::Vector3(0.0f, 1.0f, 0.0f);
	v[5].color = Math::Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	v[6].position = Math::Vector3(m_Min.x, m_Min.y, m_Max.z);
	v[6].normal = Math::Vector3(0.0f, 1.0f, 0.0f);
	v[6].color = Math::Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	v[7].position = Math::Vector3(m_Max.x, m_Min.y, m_Max.z);
	v[7].normal = Math::Vector3(0.0f, 1.0f, 0.0f);
	v[7].color = Math::Vector4(1.0f, 0.0f, 0.0f, 1.0f);

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
	graphics->GetDevice()->CreateBuffer(&bd, &sd, &pVB);

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

	graphics->GetDevice()->CreateBuffer(&bd2, &sd2, &pIB);

	DirectX::XMMATRIX world;
	world = DirectX::XMMatrixIdentity();
	graphics->SetWorldMatrix(world);

	UINT stride = sizeof(Debug::LineVertex);
	UINT offset = 0;
	graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, &pVB, &stride, &offset);

	// インデックスバッファ設定
	graphics->GetDeviceContext()->IASetIndexBuffer(pIB, DXGI_FORMAT_R32_UINT, 0);

	// プリミティブトポロジ設定
	graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// ポリゴン描画
	graphics->GetDeviceContext()->DrawIndexed(24, 0, 0);

	SAFE_RELEASE(pVB);
	SAFE_RELEASE(pIB);
#endif
}

const Math::Vector3 & OBB3::position() const
{
	return m_Position;
}

const Math::Vector3 & OBB3::GetDirection(int32_t Element)
{
	return m_Dir[Element];
}

const Math::Vector3 & OBB3::GetLength() const
{
	return m_Length;
}
#pragma endregion OBB3メソッド


#pragma region Function_Intersect
// ヘルパー関数
namespace
{
	// OBB3のヘルパー関数
	// 分離軸に投影された軸成分から投影線分長を算出
	float LengthSeparateAxis(const Math::Vector3& Sep, const Math::Vector3& E1, const Math::Vector3& E2, const Math::Vector3& E3 = Math::Vector3(0.0f, 0.0f, 0.0f))
	{
		float r1 = Math::Abs(Math::Vector3::Dot(Sep, E1));
		float r2 = Math::Abs(Math::Vector3::Dot(Sep, E2));
		float r3 = Math::Abs(Math::Vector3::Dot(Sep, E3));
		return r1 + r2 + r3;
	}

	bool TestSidePlane(float start, float end, float negd, const Math::Vector3& norm, std::vector<std::pair<float, Math::Vector3>>& out)
	{
		float denom = end - start;
		if (Math::NearZero(denom))
		{
			return false;
		}
		else
		{
			float numer = -start + negd;
			float t = numer / denom;
			// Test that t is within bounds
			if (t >= 0.0f && t <= 1.0f)
			{
				out.emplace_back(t, norm);
				return true;
			}
			else
			{
				return false;
			}
		}
	}

}

bool Intersect(const Line & l, const AABB3 & b)
{
	// Vector to save all possible t values, and normals for those sides
	std::vector<std::pair<float, Math::Vector3>> tValues;
	TestSidePlane(l.GetStart().x, l.GetEnd().x, b.GetMin().x, Math::Vector3::NegUnitX, tValues);
	TestSidePlane(l.GetStart().x, l.GetEnd().x, b.GetMax().x, Math::Vector3::UnitX, tValues);
	TestSidePlane(l.GetStart().y, l.GetEnd().y, b.GetMin().y, Math::Vector3::NegUnitY, tValues);
	TestSidePlane(l.GetStart().y, l.GetEnd().y, b.GetMax().y, Math::Vector3::UnitY, tValues);
	TestSidePlane(l.GetStart().z, l.GetEnd().z, b.GetMin().z, Math::Vector3::NegUnitZ, tValues);
	TestSidePlane(l.GetStart().z, l.GetEnd().z, b.GetMax().z, Math::Vector3::UnitZ, tValues);

	// Sort the t values in ascending order
	std::sort(tValues.begin(), tValues.end(), [](
		const std::pair<float, Math::Vector3>& a,
		const std::pair<float, Math::Vector3>& b) {
			return a.first < b.first;
		});
	// Test if the box contains any of these points of intersection
	Math::Vector3 point;
	for (auto& t : tValues)
	{
		point = l.PointOnSegment(t.first);
		if (b.Contains(point))
		{
			return true;
		}
	}

	//None of the intersections are within bounds of box
	return false;
}

bool Intersect(const AABB3 & b, const Line & l)
{
	// Vector to save all possible t values, and normals for those sides
	std::vector<std::pair<float, Math::Vector3>> tValues;
	TestSidePlane(l.GetStart().x, l.GetEnd().x, b.GetMin().x, Math::Vector3::NegUnitX, tValues);
	TestSidePlane(l.GetStart().x, l.GetEnd().x, b.GetMax().x, Math::Vector3::UnitX, tValues);
	TestSidePlane(l.GetStart().y, l.GetEnd().y, b.GetMin().y, Math::Vector3::NegUnitY, tValues);
	TestSidePlane(l.GetStart().y, l.GetEnd().y, b.GetMax().y, Math::Vector3::UnitY, tValues);
	TestSidePlane(l.GetStart().z, l.GetEnd().z, b.GetMin().z, Math::Vector3::NegUnitZ, tValues);
	TestSidePlane(l.GetStart().z, l.GetEnd().z, b.GetMax().z, Math::Vector3::UnitZ, tValues);

	// Sort the t values in ascending order
	std::sort(tValues.begin(), tValues.end(), []( 
		const std::pair<float, Math::Vector3>& a,
		const std::pair<float, Math::Vector3>& b) {
			return a.first < b.first;
		});
	// Test if the box contains any of these points of intersection
	Math::Vector3 point;
	for (auto& t : tValues)
	{
		point = l.PointOnSegment(t.first);
		if (b.Contains(point))
		{
			return true;
		}
	}

	//None of the intersections are within bounds of box
	return false;
}

bool Intersect(const Sphere3 & a, const Sphere3 & b)
{
	Math::Vector3 vec = a.GetCenter() - b.GetCenter();
 	float distsq = vec.LengthSq();
	float sumRadius = a.GetRadius() + b.GetRadius();
	if(distsq <= (sumRadius * sumRadius))
	{
		return true;
	}
	return false;
}

bool Intersect(const AABB3 & a, const AABB3 & b)
{
	Math::Vector3 minA, maxA, minB, maxB;
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
	Math::Vector3 dist = b.position() - s.GetCenter();
	float dot = Math::Vector3::Dot(dist, dist);
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
	Math::Vector3 Nae1 = obj_a.GetDirection(0);
	Math::Vector3 ae1 = Nae1 * obj_a.GetLength().x;
	Math::Vector3 Nae2 = obj_a.GetDirection(1);
	Math::Vector3 ae2 = Nae2 * obj_a.GetLength().y;
	Math::Vector3 Nae3 = obj_a.GetDirection(2);
	Math::Vector3 ae3 = Nae3 * obj_a.GetLength().z;

	Math::Vector3 Nbe1 = obj_b.GetDirection(0);
	Math::Vector3 be1 = Nae1 * obj_b.GetLength().x;
	Math::Vector3 Nbe2 = obj_b.GetDirection(1);
	Math::Vector3 be2 = Nae2 * obj_b.GetLength().y;
	Math::Vector3 Nbe3 = obj_b.GetDirection(2);
	Math::Vector3 be3 = Nae3 * obj_b.GetLength().z;

	Math::Vector3 Interval = obj_a.position() - obj_b.position();

	// 分離軸 : ae1
	float rA = ae1.Length();
	float rB = LengthSeparateAxis(Nae1, be1, be2, be3);
	float L = Math::Abs(Math::Vector3::Dot(Interval, Nae1));
	if (L > rA + rB)
	{
		return false;
	}
	 // 分離軸 : ae2
	rA = ae2.Length();
	rB = LengthSeparateAxis(Nae2, be1, be2, be3);
	L = Math::Abs(Math::Vector3::Dot(Interval, Nae2));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : ae3
	rA = ae3.Length();
	rB = LengthSeparateAxis(Nae3, be1, be2, be3);
	L = Math::Abs(Math::Vector3::Dot(Interval, Nae3));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : be1
	rA = LengthSeparateAxis(Nbe1, ae1, ae2, ae3);
	rB = be1.Length();
	L = Math::Abs(Math::Vector3::Dot(Interval, Nbe1));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : be2
	rA = LengthSeparateAxis(Nbe2, ae1, ae2, ae3);
	rB = be2.Length();
	L = Math::Abs(Math::Vector3::Dot(Interval, Nbe2));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : be3
	rA = LengthSeparateAxis(Nbe3, ae1, ae2, ae3);
	rB = be3.Length();
	L = Math::Abs(Math::Vector3::Dot(Interval, Nbe3));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C11
	Math::Vector3 cross;
	cross = Math::Vector3::Cross(Nae1, Nbe1);
	rA = LengthSeparateAxis(cross, ae2, ae3);
	rB = LengthSeparateAxis(cross, be2, be3);
	L = Math::Abs(Math::Vector3::Dot(Interval, cross));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : C12
	cross = Math::Vector3::Cross(Nae1, Nbe2);
	rA = LengthSeparateAxis(cross, ae2, ae3);
	rB = LengthSeparateAxis(cross, be1, be3);
	L = Math::Abs(Math::Vector3::Dot(Interval, cross));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : C13
	cross = Math::Vector3::Cross(Nae1, Nbe3);
	rA = LengthSeparateAxis(cross, ae2, ae3);
	rB = LengthSeparateAxis(cross, be1, be2);
	L = Math::Abs(Math::Vector3::Dot(Interval, cross));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : C21
	cross = Math::Vector3::Cross(Nae2, Nbe1);
	rA = LengthSeparateAxis(cross, ae1, ae3);
	rB = LengthSeparateAxis(cross, be2, be3);
	L = Math::Abs(Math::Vector3::Dot(Interval, cross));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : C22
	cross = Math::Vector3::Cross(Nae2, Nbe2);
	rA = LengthSeparateAxis(cross, ae1, ae3);
	rB = LengthSeparateAxis(cross, be1, be3);
	L = Math::Abs(Math::Vector3::Dot(Interval, cross));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : C23
	cross = Math::Vector3::Cross(Nae2, Nbe3);
	rA = LengthSeparateAxis(cross, ae1, ae3);
	rB = LengthSeparateAxis(cross, be1, be2);
	L = Math::Abs(Math::Vector3::Dot(Interval, cross));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : C31
	cross = Math::Vector3::Cross(Nae3, Nbe1);
	rA = LengthSeparateAxis(cross, ae1, ae2);
	rB = LengthSeparateAxis(cross, be2, be3);
	L = Math::Abs(Math::Vector3::Dot(Interval, cross));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : C32
	cross = Math::Vector3::Cross(Nae3, Nbe2);
	rA = LengthSeparateAxis(cross, ae1, ae2);
	rB = LengthSeparateAxis(cross, be1, be3);
	L = Math::Abs(Math::Vector3::Dot(Interval, cross));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : C33
	cross = Math::Vector3::Cross(Nae3, Nbe3);
	rA = LengthSeparateAxis(cross, ae1, ae2);
	rB = LengthSeparateAxis(cross, be1, be2);
	L = Math::Abs(Math::Vector3::Dot(Interval, cross));
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
	Math::Vector3 x = p.GetOldCenter() - q.GetOldCenter();
	Math::Vector3 y = p.GetCenter() - p.GetOldCenter() - (q.GetCenter() - q.GetOldCenter());
	float a = Math::Vector3::Dot(y, y);
	float b = 2.0f * Math::Vector3::Dot(x, y);
	float sumRadius = p.GetRadius() + q.GetRadius();
	float c = Math::Vector3::Dot(x, x) - sumRadius * sumRadius;
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