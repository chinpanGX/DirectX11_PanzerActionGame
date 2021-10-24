/*------------------------------------------------------------
	
	[Collision.h]
	Author : 出合翔太

	当たり判定を検知するクラス、関数をまとめる

-------------------------------------------------------------*/
#pragma once
#include "myLib.h"

// line
class Line final
{
public:
	Line() = delete;
	Line(const Math::Vector3 start, const Math::Vector3 end);
	// 位置、方向ベクトル、長さ
	void Update(const Math::Vector3& pos, const Math::Vector3& vec, float distance);
	// 0<=t<=1
	Math::Vector3 PointOnSegment(float t)const;
	// 点とライン間の最小距離の2乗を取得
	float MinDistSq(const Math::Vector3& point)const;
	// 2つの線分の間
	static float MinDistSq(const Line& s1, const Line& s2);
	const Math::Vector3& GetStart()const;
	const Math::Vector3& GetEnd()const;
private:
	Math::Vector3 m_Start;
	Math::Vector3 m_End;
};

// 平面
class Plane3 final
{
public:
	Plane3() = delete;
	Plane3(const Math::Vector3& a, const Math::Vector3& b, const Math::Vector3& c);

	Math::Vector3 m_Normal; // 平面の法線
	float m_Distance; // 最短距離
};

// 球
class Sphere3 final
{
public:
	Sphere3() = delete;
	Sphere3(const Math::Vector3& Position, float Radius);
	~Sphere3();
	void Update(const Math::Vector3& Position);
	void Update();
	const Math::Vector3& GetCenter()const;
	const Math::Vector3& GetOldCenter() const; // 1f前の位置
	const float GetRadius()const;
private:
	Math::Vector3 m_Center;
	Math::Vector3 m_oldCenter;
	float m_Radius;
};

// AABB
class AABB3 final
{
public:
	AABB3() = delete;
	AABB3(const Math::Vector3& Center, const Math::Vector3& Size);
	~AABB3();
	
	// デバッグ表示用の設定
	void SystemDraw();

	void Update(const Math::Vector3& Position);
	void Update(const Math::Vector3 & Position, const Math::Quaternion& Rot);
	bool Contains(const Math::Vector3& point) const;
	float MinDistSq(const Math::Vector3& Position)const;
	// Getter
	const Math::Vector3& GetMin() const;
	const Math::Vector3& GetMax() const;
private:
	void UpdateRotate(const Math::Quaternion& Rot);
	void UpdateMinMax(const Math::Vector3& Point);

	Math::Quaternion m_Rotation;
	Math::Vector3 m_Center;
	Math::Vector3 m_Size;
	Math::Vector3 m_Min;
	Math::Vector3 m_Max;
};

// OBB
class OBB3 final
{
public:
	OBB3() = delete;
	OBB3(const class Transform& t, const Math::Vector3& Size);
	~OBB3();
	void Update(const Math::Vector3& Position, const class Transform& t);
	void SystemDraw();
	const Math::Vector3& GetPosition()const;
	const Math::Vector3& GetDirection(int32_t Element);
	const Math::Vector3& GetLength()const;
private:
	Math::Vector3 m_Position;
	Math::Vector3 m_Dir[3];
	Math::Vector3 m_Length;
	Math::Vector3 m_Size;
	Math::Vector3 m_Min;
	Math::Vector3 m_Max;
};

// 当たり判定検知
bool Intersect(const Line& l, const AABB3& b);
bool Intersect(const AABB3& b, const Line& l);
bool Intersect(const Sphere3& a, const Sphere3& b);
bool Intersect(const Sphere3& s, const AABB3& b);
bool Intersect(const AABB3& b, const Sphere3& s);
bool Intersect(const AABB3& a, const AABB3& b);
bool Intersect(const Sphere3& s, const OBB3& b);
bool Intersect(const OBB3& a, const OBB3& b);

// 連続衝突検知
// 0が前フレーム、1現在のフレーム
bool CCD(const Sphere3& p, const Sphere3& q, float& t);