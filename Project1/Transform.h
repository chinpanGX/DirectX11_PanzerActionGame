/*-------------------------------------------------------------

	[Transform.h]
	Author : 出合翔太

	座標、回転、大きさを持つ

--------------------------------------------------------------*/
#pragma once
#include "myLib.h"

class Transform final
{
public:
	// デフォルト
	inline Transform() : m_Position(Math::Vector3::Zero), m_Rotation(Math::Quaternion::Identity), m_Scale(Math::Vector3::One) { }
	inline ~Transform() { }

	void Set(const Math::Vector3& position = Math::Vector3::Zero, const Math::Vector3& scale = Math::Vector3::One, const Math::Quaternion& rotation = Math::Quaternion::Identity)
	{
		m_Position = position;
		m_Scale = scale;
		m_Rotation = rotation;
	}
	
	void Begin()
	{
		m_Position = Math::Vector3::Zero;
		m_Rotation = Math::Quaternion::Identity;
		m_Scale = Math::Vector3::One;
	}

	// ベクトルの方向
	enum Vector : int32_t
	{
		Right,
		Left,
		Up,
		Down,
		Forward,
		Backward
	};

	// プロパティ
	inline Math::Vector3& position()	   { return this->m_Position; }
	inline Math::Quaternion& rotation() { return this->m_Rotation; }
	inline Math::Vector3& scale()	   { return this->m_Scale; }
	
	inline void position(Math::Vector3 pos)    { this->m_Position = pos; }
	inline void rotation(Math::Quaternion rot) { this->m_Rotation = rot; }
	inline void scale(Math::Vector3 scl)	      { this->m_Scale = scl; }
	
	inline void position(float x, float y, float z)			{ this->m_Position = Math::Vector3(x, y, z); }
	inline void rotation(float x, float y, float z, float w){ this->m_Rotation = Math::Quaternion(x, y, z, w); }
	inline void rotation(Math::Vector3 v, float angle)		{ this->m_Rotation = Math::Quaternion(v, angle); }
	inline void scale(float s)								{ this->m_Scale = Math::Vector3(s, s, s); }
	inline void scale(float x, float y, float z)			{ this->m_Scale = Math::Vector3(x, y, z); }


	// 指定した方向ベクトルを返す
	inline Math::Vector3 GetVector(Vector v)
	{
		DirectX::XMMATRIX rot = DirectX::XMMatrixRotationRollPitchYaw(this->m_Rotation.x, this->m_Rotation.y, this->m_Rotation.z);
		Math::Vector3 vector;
		switch (v)
		{
			// 左右
		case 0:
		case 1:
			vector.x = rot.r[0].m128_f32[0];
			vector.y = rot.r[0].m128_f32[1];
			vector.z = rot.r[0].m128_f32[2];
			break;
			// 上下
		case 2:
		case 3:
			vector.x = rot.r[1].m128_f32[0];
			vector.y = rot.r[1].m128_f32[1];
			vector.z = rot.r[1].m128_f32[2];
			break;
			// 前後
		case 4:
		case 5:
			vector.x = rot.r[2].m128_f32[0];
			vector.y = rot.r[2].m128_f32[1];
			vector.z = rot.r[2].m128_f32[2];
			break;
		}

		if (v % 2 == 1)
		{
			vector.x *= -1;
			vector.y *= -1;
			vector.z *= -1;
		}
		return vector;
	}

private:
	Math::Vector3	 m_Position;
	Math::Vector3	 m_Scale;
	Math::Quaternion m_Rotation;
};

