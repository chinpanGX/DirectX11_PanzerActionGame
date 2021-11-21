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
	inline Transform() : m_Position(D3DXVECTOR3(0.0f, 0.0f, 0.0f)), m_Rotation(0.0f, 0.0f, 0.0f), m_Scale(1.0f, 1.0f, 1.0f) {}
	inline ~Transform() { }

	inline void Begin()
	{
		m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}

	inline void Set(D3DXVECTOR3 Pos, D3DXVECTOR3 Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3 Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		m_Position = Pos;
		m_Scale = Scl;
		m_Rotation = Rot;
	}

	// プロパティ
	inline D3DXVECTOR3& position() { return this->m_Position; }
	inline D3DXVECTOR3& rotation() { return this->m_Rotation; }
	inline D3DXVECTOR3& scale()	   { return this->m_Scale; }
	
	inline void position(D3DXVECTOR3 pos)    { this->m_Position = pos; }
	inline void rotation(D3DXVECTOR3 rot) { this->m_Rotation = rot; }
	inline void scale(D3DXVECTOR3 scl)	      { this->m_Scale = scl; }
	
	inline void position(float x, float y, float z)			{ this->m_Position = D3DXVECTOR3(x, y, z); }
	inline void rotation(float x, float y, float z, float w){ this->m_Rotation = D3DXVECTOR3(x, y, z); }
	inline void scale(float s)								{ this->m_Scale = D3DXVECTOR3(s, s, s); }
	inline void scale(float x, float y, float z)			{ this->m_Scale = D3DXVECTOR3(x, y, z); }

	// ベクトルを返す
	inline D3DXVECTOR3 right()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);
		D3DXVECTOR3 vector;
		vector.x = rot._11;
		vector.y = rot._12;
		vector.z = rot._13;
		return vector;
	}

	inline D3DXVECTOR3 up()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);
		D3DXVECTOR3 vector;
		vector.x = rot._21;
		vector.y = rot._22;
		vector.z = rot._23;
		return vector;
	}

	inline D3DXVECTOR3 forward()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);
		D3DXVECTOR3 vector;
		vector.x = rot._31;
		vector.y = rot._32;
		vector.z = rot._33;
		return vector;
	}
private:
	D3DXVECTOR3	m_Position;
	D3DXVECTOR3	m_Scale;
	D3DXVECTOR3 m_Rotation;
};

