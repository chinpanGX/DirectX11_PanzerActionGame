/*------------------------------------------------------------
	
	[Collision.h]
	Author : 出合翔太

	当たり判定を検知するクラス、関数をまとめる

-------------------------------------------------------------*/
#pragma once
#include "Transform.h"
#include "myLib.h"

// 球
class Sphere3 final
{
public:
	Sphere3() = delete;
	Sphere3(const D3DXVECTOR3& Position, float Radius);
	~Sphere3();
	void Update(const D3DXVECTOR3& Position);
	void Update();
	const D3DXVECTOR3& GetCenter()const;
	const D3DXVECTOR3& GetOldCenter() const; // 1f前の位置
	const float GetRadius()const;
private:
	D3DXVECTOR3 m_Center;
	D3DXVECTOR3 m_oldCenter;
	float m_Radius;
};

// AABB
class AABB3 final
{
public:
	AABB3() = delete;
	AABB3(const D3DXVECTOR3& Center, const D3DXVECTOR3& Size);
	~AABB3();
	
	// デバッグ表示用の設定
	void SystemDraw();

	void Update(const D3DXVECTOR3& Position);
	void Update(const D3DXVECTOR3 & Position, const D3DXVECTOR3& Rot);
	bool Contains(const D3DXVECTOR3& point) const;
	float MinDistSq(const D3DXVECTOR3& Position)const;
	// Getter
	const D3DXVECTOR3& GetMin() const;
	const D3DXVECTOR3& GetMax() const;
private:
	void UpdateMinMax(const D3DXVECTOR3& Point);

	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Center;
	D3DXVECTOR3 m_Size;
	D3DXVECTOR3 m_Min;
	D3DXVECTOR3 m_Max;
};

// OBB
class OBB3 final
{
public:
	enum Vector
	{
		right,
		up,
		forward
	};
	OBB3() = delete;
	OBB3(const class Transform& t, const D3DXVECTOR3& Size);
	~OBB3();
	void Update(const D3DXVECTOR3& Position, const Transform& t);
	void SystemDraw();
	const D3DXVECTOR3& GetPosition()const;
	const D3DXVECTOR3& direction(Vector vector)const;
	const float length(Vector vector)const;
private:
	Transform m_Transform;
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Direction[3];
	float m_DirectLength[3];
};

// 当たり判定検知
bool Intersect(const Sphere3& a, const Sphere3& b);
bool Intersect(const Sphere3& s, const AABB3& b);
bool Intersect(const AABB3& b, const Sphere3& s);
bool Intersect(const AABB3& a, const AABB3& b);
bool Intersect(const Sphere3& s, const OBB3& b);
bool Intersect(const OBB3& a, const OBB3& b);

// 連続衝突検知
// 0が前フレーム、1現在のフレーム
bool CCD(const Sphere3& p, const Sphere3& q, float& t);