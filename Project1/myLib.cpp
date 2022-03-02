/*--------------------------------------------------------------

	[myLib.cpp]
	Author : 出合翔太　

	自作の便利なものをまとめる

	Math : 算術ライブラリ
	myLib : 便利なクラス、関数

---------------------------------------------------------------*/
#include "myLib.h"
#include <mutex>

#pragma region Timeline_method
myLib::Timeline::Timeline(float Start, float End, float Rate) : m_Interval(Start, End), m_Rate(Rate)
{
}

void myLib::Timeline::Start(float& v)
{
	v += m_Rate;
	if (v > m_Interval.upper())
	{
		v = m_Interval.upper();
	}
}

void myLib::Timeline::Reverce(float& v)
{
	v -= m_Rate;
	if (v < m_Interval.lower())
	{
		v = m_Interval.lower();
	}
}

void myLib::Timeline::SetRate(float Transform)
{
	m_Rate = Transform;
}
#pragma endregion Timelineのメソッド

void Math::Matrix::MatrixScaling(D3DXMATRIX* m, D3DXVECTOR3 Scale)
{
	D3DXMatrixScaling(m, Scale.x, Scale.y, Scale.z);
}

void Math::Matrix::MatrixRotationRollPitchYaw(D3DXMATRIX* m, D3DXVECTOR3 Rotation)
{
	D3DXMatrixRotationYawPitchRoll(m, Rotation.y, Rotation.x, Rotation.z);
}

void Math::Matrix::MatrixTranslation(D3DXMATRIX* m, D3DXVECTOR3 Position)
{
	D3DXMatrixTranslation(m, Position.x, Position.y, Position.z);
}
