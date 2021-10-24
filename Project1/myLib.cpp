/*--------------------------------------------------------------

	[myLib.cpp]
	Author : 出合翔太　

	自作の便利なものをまとめる

	Math : 算術ライブラリ
	myLib : 便利なクラス、関数

---------------------------------------------------------------*/
#include "myLib.h"
#include <mutex>

#pragma region Math
// const static メンバ変数の定義
// Vector2、Math::Vector3のみ
const Math::Vector2 Math::Vector2::Zero(0.0f, 0.0f);
const Math::Vector2 Math::Vector2::UnitX(1.0f, 0.0f);
const Math::Vector2 Math::Vector2::UnitY(0.0f, 1.0f);
const Math::Vector2 Math::Vector2::NegUnitX(-1.0f, 0.0f);
const Math::Vector2 Math::Vector2::NegUnitY(0.0f, -1.0f);

const Math::Vector3 Math::Vector3::Zero(0.0f, 0.0f, 0.f);
const Math::Vector3 Math::Vector3::One(1.0f, 1.0f, 1.0f);
const Math::Vector3 Math::Vector3::UnitX(1.0f, 0.0f, 0.0f);
const Math::Vector3 Math::Vector3::UnitY(0.0f, 1.0f, 0.0f);
const Math::Vector3 Math::Vector3::UnitZ(0.0f, 0.0f, 1.0f);
const Math::Vector3 Math::Vector3::NegUnitX(-1.0f, 0.0f, 0.0f);
const Math::Vector3 Math::Vector3::NegUnitY(0.0f, -1.0f, 0.0f);
const Math::Vector3 Math::Vector3::NegUnitZ(0.0f, 0.0f, -1.0f);
const Math::Vector3 Math::Vector3::Infinity(Math::Infinity, Math::Infinity, Math::Infinity);
const Math::Vector3 Math::Vector3::NegInfinity(Math::NegInfinity, Math::NegInfinity, Math::NegInfinity);

#pragma region method of Math::Vector3
Math::Vector3 Math::Vector3::Transform(const Math::Vector3 & v, const Math::Quaternion & q)
{
	// v + 2.0*cross(q.xyz, cross(q.xyz,v) + q.w*v);
	Math::Vector3 qv(q.x, q.y, q.z);
	Math::Vector3 retVal = v;
	retVal += 2.0f * Math::Vector3::Cross(qv, Math::Vector3::Cross(qv, v) + q.w * v);
	return retVal;
}

Math::Vector3 Math::Vector3::Transform(const Vector3 & v, const DirectX::XMMATRIX m)
{
	DirectX::XMVECTOR tmp = DirectX::XMVector3Transform(Vector3::CastXMVECTOR(v), m);
	return Vector3(tmp);
}

Math::Vector3 Math::Vector3::TransformCoord(const Vector3 & v, const DirectX::XMMATRIX m)
{
	DirectX::XMVECTOR tmp = DirectX::XMVector3TransformCoord(Vector3::CastXMVECTOR(v), m);
	return Vector3(tmp);
}

#pragma endregion Math::Vector3のメソッド
#pragma region method of Math::Vector4
// Math::Vector4
Math::Vector4::Vector4()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}
Math::Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
void Math::Vector4::Set(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float Math::Vector4::Length()
{
	return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2) + powf(w, 2));
}

void Math::Vector4::Normalize()
{
	float length = Length();
	x /= length;
	y /= length;
	z /= length;
}

Math::Vector4 Math::Vector4::Normalize(Math::Vector4 vec)
{
	float length = vec.Length();
	vec.x /= length;
	vec.y /= length;
	vec.z /= length;
	return vec;
}

const Math::Vector4 Math::Vector4::operator+(const Math::Vector4& vec) const
{
	return Math::Vector4(this->x + vec.x, this->y + vec.y, this->z + vec.z, this->w + vec.w);
}
const Math::Vector4 Math::Vector4::operator-(const Math::Vector4& vec) const
{
	return Math::Vector4(this->x - vec.x, this->y - vec.y, this->z - vec.z, this->w - vec.w);
}
Math::Vector4& Math::Vector4::operator+=(const Math::Vector4& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	w += vec.w;
	return *this;
}
#pragma endregion Math::Vector4クラスのメンバ関数

#pragma region method of Math::Quaternion
const Math::Quaternion Math::Quaternion::Identity(0.0f, 0.0f, 0.0f, 1.0f);

Math::Quaternion::Quaternion()
{
	*this = Math::Quaternion::Identity;
}

Math::Quaternion::Quaternion(float x, float y, float z, float w)
{
	Set(x, y, z, w);
}

Math::Quaternion::Quaternion(const Math::Vector3 & axis, float angle)
{
	float scalar = Math::Sin(angle / 2.0f);
	x = axis.x * scalar;
	y = axis.y * scalar;
	z = axis.z * scalar;
	w = Math::Cos(angle / 2.0f);
}

void Math::Quaternion::Set(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void Math::Quaternion::Conjugate()
{
	x *= -1.0f;
	y *= -1.0f;
	z *= -1.0f;
}

float Math::Quaternion::LengthSq() const
{
	return Math::Sqrt(x * x + y * y + z * z* +w * w);
}

float Math::Quaternion::Length() const
{
	return Math::Sqrt(LengthSq());
}

void Math::Quaternion::Normalize()
{
	float length = Length();
	x /= length;
	y /= length;
	z /= length;
	w /= length;
}

Math::Quaternion Math::Quaternion::Normalize(const Math::Quaternion & q)
{
	Math::Quaternion relVal = q;
	relVal.Normalize();
	return relVal;
}

Math::Quaternion Math::Quaternion::Lerp(const Math::Quaternion & a, const Math::Quaternion & b, float f)
{
	Math::Quaternion retVal;
	retVal.x = Math::Lerp(a.x, b.x, f);
	retVal.y = Math::Lerp(a.y, b.y, f);
	retVal.z = Math::Lerp(a.z, b.z, f);
	retVal.w = Math::Lerp(a.w, b.w, f);
	retVal.Normalize();
	return retVal;
}

float Math::Quaternion::Dot(const Math::Quaternion & a, const Math::Quaternion & b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Math::Quaternion Math::Quaternion::Slerp(const Math::Quaternion & a, const Math::Quaternion & b, float f)
{
	float rawCosm = Math::Quaternion::Dot(a, b);

	float cosom = -rawCosm;
	if (rawCosm >= 0.0f)
	{
		cosom = rawCosm;
	}

	float scale0, scale1;

	if (cosom < 0.9999f)
	{
		const float omega = Math::Acos(cosom);
		const float invSin = 1.f / Math::Sin(omega);
		scale0 = Math::Sin((1.f - f) * omega) * invSin;
		scale1 = Math::Sin(f * omega) * invSin;
	}
	else
	{
		// Use linear interpolation if the quaternions
		// are collinear
		scale0 = 1.0f - f;
		scale1 = f;
	}

	if (rawCosm < 0.0f)
	{
		scale1 = -scale1;
	}

	Math::Quaternion retVal;
	retVal.x = scale0 * a.x + scale1 * b.x;
	retVal.y = scale0 * a.y + scale1 * b.y;
	retVal.z = scale0 * a.z + scale1 * b.z;
	retVal.w = scale0 * a.w + scale1 * b.w;
	retVal.Normalize();
	return retVal;
}

Math::Quaternion Math::Quaternion::Concatenate(const Math::Quaternion & q, const Math::Quaternion & p)
{
	Math::Quaternion retVal;

	// Vector component is:
	// ps * qv + qs * pv + pv x qv
	Math::Vector3 qv(q.x, q.y, q.z);
	Math::Vector3 pv(p.x, p.y, p.z);
	Math::Vector3 newVec = p.w * qv + q.w * pv + Math::Vector3::Cross(pv, qv);
	retVal.x = newVec.x;
	retVal.y = newVec.y;
	retVal.z = newVec.z;

	// Scalar component is:
	// ps * qs - pv . qv
	retVal.w = p.w * q.w - Math::Vector3::Dot(pv, qv);

	return retVal;
}
#pragma endregion Math::Quaternionクラスのメンバ関数

DirectX::XMMATRIX Math::Matrix::MatrixScaling(Vector3 Scale)
{
	DirectX::XMMATRIX tmp = DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z);
	return tmp;
}

DirectX::XMMATRIX Math::Matrix::MatrixRotationQuatrnion(Quaternion Quaternion)
{
	DirectX::XMMATRIX tmp = DirectX::XMMatrixRotationQuaternion(Math::Quaternion::CastXMVECTOR(Quaternion));
	return tmp;
}

DirectX::XMMATRIX Math::Matrix::MatrixRotationQuatrnionRollPitchYaw(Quaternion Quaternion)
{
	Vector3 v = Vector3(Quaternion.x, Quaternion.y, Quaternion.z);
	Vector3 tmp = v.Transform(v, Quaternion);
	return  MatrixRotationRollPitchYaw(tmp);
}

DirectX::XMMATRIX Math::Matrix::MatrixRotationRollPitchYaw(Vector3 Rotation)
{
	DirectX::XMMATRIX tmp = DirectX::XMMatrixRotationRollPitchYaw(Rotation.x, Rotation.y, Rotation.z);
	return tmp;
}

DirectX::XMMATRIX Math::Matrix::MatrixTranslation(Vector3 Position)
{
	DirectX::XMMATRIX tmp = DirectX::XMMatrixTranslation(Position.x, Position.y, Position.z);
	return tmp;
}
#pragma endregion Math

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

void myLib::Timeline::SetRate(float t)
{
	m_Rate = t;
}
#pragma endregion Timelineのメソッド
