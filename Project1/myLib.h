/*--------------------------------------------------------------

	[myLib.h]
	Author : 出合翔太　

	自作の便利なものをまとめる

	Math : 算術ライブラリ
	myLib : 便利なクラス、関数

---------------------------------------------------------------*/
#pragma once
#include "stdafx.h"
#include <math.h>
#include <time.h>
#include <functional>
#include <boost/numeric/interval.hpp>
#include <boost/numeric/interval/io.hpp>
#include <typeinfo>

// 算術ライブラリ
namespace Math
{
#pragma region Math_Function
	constexpr float Pi = 3.1415926535f;
	constexpr float TwoPi = Pi * 2.0f;
	constexpr float PiOver2 = Pi / 2.0f;
	constexpr float Infinity = std::numeric_limits<float>::infinity();
	constexpr float NegInfinity = -std::numeric_limits<float>::infinity();

	inline float ToRadians(float degrees)
	{
		return degrees * Pi / 180.0f;
	}

	inline float ToDegrees(float radians)
	{
		return radians * 180.0f / Pi;
	}

	inline bool NearZero(float val, float epsilon = 0.001f)
	{
		if (fabs(val) <= epsilon)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	inline T Max(const T& a, const T& b)
	{
		return (a < b ? b : a);
	}

	template <typename T>
	inline T Min(const T& a, const T& b)
	{
		return (a < b ? a : b);
	}

	template <typename T>
	inline T Clamp(const T& value, const T& lower, const T& upper)
	{
		return Min(upper, Max(lower, value));
	}


	inline float Abs(float value)
	{
		return fabs(value);
	}

	inline float Cos(float angle)
	{
		return cosf(angle);
	}

	inline float Sin(float angle)
	{
		return sinf(angle);
	}

	inline float Tan(float angle)
	{
		return tanf(angle);
	}

	inline float Acos(float value)
	{
		return acosf(value);
	}

	inline float Atan2(float y, float x)
	{
		return atan2f(y, x);
	}

	inline float Cot(float angle)
	{
		return 1.0f / Tan(angle);
	}

	inline float Lerp(float a, float b, float f)
	{
		//return a + f * (b - a);
		return (1 - f) * a + f* b;
	}

	inline float Sqrt(float value)
	{
		return sqrtf(value);
	}

	inline float Fmod(float numer, float denom)
	{
		return fmod(numer, denom);
	}
#pragma endregion 計算関数

#pragma region Vector2
	class Vector2 final
	{
	public:
		float x;
		float y;

		inline Vector2() : x(0.0f), y(0.0f) {}

		inline explicit Vector2(float s) : x(s), y(s) {}

		inline explicit Vector2(float inX, float inY) : x(inX), y(inY) {}

		inline static DirectX::XMFLOAT2 CastXMFlaot2(Vector2 v)
		{
			return DirectX::XMFLOAT2(v.x, v.y);
		}

		// Set both components in one line
		inline void Set(float inX, float inY)
		{
			x = inX;
			y = inY;
		}

		// Vector addition (a + b)
		inline friend Vector2 operator+(const Vector2& a, const Vector2& b)
		{
			return Vector2(a.x + b.x, a.y + b.y);
		}

		// Vector subtraction (a - b)
		inline friend Vector2 operator-(const Vector2& a, const Vector2& b)
		{
			return Vector2(a.x - b.x, a.y - b.y);
		}

		// Component-wise multiplication
		// (a.x * b.x, ...)
		inline friend Vector2 operator*(const Vector2& a, const Vector2& b)
		{
			return Vector2(a.x * b.x, a.y * b.y);
		}

		// Scalar multiplication
		inline friend Vector2 operator*(const Vector2& vec, float scalar)
		{
			return Vector2(vec.x * scalar, vec.y * scalar);
		}

		// Scalar multiplication
		inline friend Vector2 operator*(float scalar, const Vector2& vec)
		{
			return Vector2(vec.x * scalar, vec.y * scalar);
		}

		// Scalar *=
		inline Vector2& operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		// Vector +=
		inline Vector2& operator+=(const Vector2& right)
		{
			x += right.x;
			y += right.y;
			return *this;
		}

		// Vector -=
		inline Vector2& operator-=(const Vector2& right)
		{
			x -= right.x;
			y -= right.y;
			return *this;
		}

		// Length squared of vector
		inline float LengthSq() const
		{
			return (x*x + y * y);
		}

		// Length of vector
		inline float Length() const
		{
			return (Math::Sqrt(LengthSq()));
		}

		// Normalize this vector
		inline void Normalize()
		{
			float length = Length();
			x /= length;
			y /= length;
		}

		// Normalize the provided vector
		inline static Vector2 Normalize(const Vector2& vec)
		{
			Vector2 temp = vec;
			temp.Normalize();
			return temp;
		}

		// Dot product between two vectors (a dot b)
		inline static float Dot(const Vector2& a, const Vector2& b)
		{
			return (a.x * b.x + a.y * b.y);
		}

		// Lerp from A to B by f
		inline static Vector2 Lerp(const Vector2& a, const Vector2& b, float f)
		{
			return Vector2(a + f * (b - a));
		}

		// Reflect V about (normalized) N
		inline static Vector2 Reflect(const Vector2& v, const Vector2& n)
		{
			return v - 2.0f * Vector2::Dot(v, n) * n;
		}

		static const Vector2 Zero;
		static const Vector2 UnitX;
		static const Vector2 UnitY;
		static const Vector2 NegUnitX;
		static const Vector2 NegUnitY;
	};
#pragma endregion Vector2クラス

#pragma region Vector3
	class Vector3 final
	{
	public:
		float x;
		float y;
		float z;

		inline Vector3() :x(0.0f), y(0.0f), z(0.0f) {}

		inline explicit Vector3(float s) : x(s), y(s), z(s) {}

		inline explicit Vector3(float inX, float inY, float inZ) : x(inX), y(inY), z(inZ) {}

		inline explicit Vector3(DirectX::XMFLOAT3 v) : x(v.x), y(v.y), z(v.z) {}

		inline explicit Vector3(DirectX::XMVECTOR v)
		{
			DirectX::XMFLOAT3 tmp;
			DirectX::XMStoreFloat3(&tmp, v);
			x = tmp.x;
			y = tmp.y;
			z = tmp.z;
		}

		// XMFloat3型に変換
		inline static DirectX::XMFLOAT3 CastXMFloat3(Vector3 v)
		{
			return DirectX::XMFLOAT3(v.x, v.y, v.z);
		}

		// XMVECTOR型に変換
		inline static DirectX::XMVECTOR CastXMVECTOR(Vector3 v)
		{
			DirectX::XMFLOAT3 tmp = CastXMFloat3(v);
			return DirectX::XMLoadFloat3(&tmp);
		}

		// Cast to a const float pointer
		inline const float* GetAsFloatPtr() const
		{
			return reinterpret_cast<const float*>(&x);
		}

		// Set all three components in one line
		inline void Set(float inX, float inY, float inZ)
		{
			x = inX;
			y = inY;
			z = inZ;
		}

		// Vector addition (a + b)
		inline friend Vector3 operator+(const Vector3& a, const Vector3& b)
		{
			DirectX::XMVECTOR tmp_a = Vector3::CastXMVECTOR(a);
			DirectX::XMVECTOR tmp_b = Vector3::CastXMVECTOR(b);
			return Vector3(DirectX::XMVectorAdd(tmp_a, tmp_b));
		}

		// Vector subtraction (a - b)
		inline friend Vector3 operator-(const Vector3& a, const Vector3& b)
		{
			DirectX::XMVECTOR tmp_a = Vector3::CastXMVECTOR(a);
			DirectX::XMVECTOR tmp_b = Vector3::CastXMVECTOR(b);
			return Vector3(DirectX::XMVectorSubtract(tmp_a, tmp_b));
		}

		// Component-wise multiplication
		inline friend Vector3 operator*(const Vector3& left, const Vector3& right)
		{
			return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
		}

		// Scalar multiplication
		inline friend Vector3 operator*(const Vector3& vec, float scalar)
		{
			DirectX::XMVECTOR tmp = Vector3::CastXMVECTOR(vec);
			return Vector3(DirectX::XMVectorScale(tmp, scalar));
		}

		// Scalar multiplication
		inline friend Vector3 operator*(float scalar, const Vector3& vec)
		{
			DirectX::XMVECTOR tmp = Vector3::CastXMVECTOR(vec);
			return Vector3(DirectX::XMVectorScale(tmp, scalar));
		}

		// Scalar *=
		inline Vector3& operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		// Vector +=
		inline Vector3& operator+=(const Vector3& right)
		{
			DirectX::XMVECTOR tmp = Vector3::CastXMVECTOR(*this);
			DirectX::XMVECTOR vRight = Vector3::CastXMVECTOR(right);
			*this = Vector3(DirectX::XMVectorAdd(tmp, vRight));
			return *this;
		}

		// Vector -=
		inline Vector3& operator-=(const Vector3& right)
		{
			DirectX::XMVECTOR tmp = Vector3::CastXMVECTOR(*this);
			DirectX::XMVECTOR vRight = Vector3::CastXMVECTOR(right);
			*this = Vector3(DirectX::XMVectorSubtract(tmp, vRight));
			return *this;
		}

		// Length squared of vector
		inline float LengthSq() const
		{
			return (x * x + y * y + z * z);
		}

		// Length of vector
		inline float Length() const
		{
			return (Math::Sqrt(LengthSq()));
		}

		// Normalize this vector
		inline void Normalize()
		{
			float length = Length();
			x /= length;
			y /= length;
			z /= length;
		}

		// Normalize the provided vector
		inline static Vector3 Normalize(const Vector3& vec)
		{
			Vector3 temp = vec;
			temp.Normalize();
			return temp;
		}

		// Dot product between two vectors (a dot b)
		inline static float Dot(const Vector3& a, const Vector3& b)
		{
			return (a.x * b.x + a.y * b.y + a.z * b.z);
		}

		// Cross product between two vectors (a cross b)
		inline static Vector3 Cross(const Vector3& a, const Vector3& b)
		{
			Vector3 temp;
			temp.x = a.y * b.z - a.z * b.y;
			temp.y = a.z * b.x - a.x * b.z;
			temp.z = a.x * b.y - a.y * b.x;
			return temp;
		}

		// Lerp from A to B by f
		inline static Vector3 Lerp(const Vector3& a, const Vector3& b, float f)
		{
			return Vector3(a + f * (b - a));
		}

		// Reflect V about (normalized) N
		inline static Vector3 Reflect(const Vector3& v, const Vector3& n)
		{
			return v - 2.0f * Vector3::Dot(v, n) * n;
		}

		// Transform a Vector3 by a quaternion
		static Vector3 Transform(const Vector3& v, const class Quaternion& q);
		static Vector3 Transform(const Vector3& v, const DirectX::XMMATRIX m);
		static Vector3 TransformCoord(const Vector3& v, const DirectX::XMMATRIX m);

		static const Vector3 Zero;
		static const Vector3 One;
		static const Vector3 UnitX;
		static const Vector3 UnitY;
		static const Vector3 UnitZ;
		static const Vector3 NegUnitX;
		static const Vector3 NegUnitY;
		static const Vector3 NegUnitZ;
		static const Vector3 Infinity;
		static const Vector3 NegInfinity;
	};
#pragma endregion Vector3クラス

#pragma region Vector4
	class Vector4 final
	{
	public:
		float x;
		float y;
		float z;
		float w;

		Vector4();
		Vector4(float x, float y, float z, float w);
		// XMFloat4型に変換
		inline static DirectX::XMFLOAT4 CastXMFloat4(Vector4 v)
		{
			return DirectX::XMFLOAT4(v.x, v.y, v.z, v.w);
		}
		

		void Set(float x, float y, float z, float w);
		float Length();
		void Normalize();
		static Vector4 Normalize(Vector4 vec);

		const Vector4 operator+(const Vector4& vec) const;
		const Vector4 operator-(const Vector4& vec) const;
		Vector4& operator+=(const Vector4& vec);
	};
#pragma endregion Vector4クラス

#pragma region Quaternion
	class Quaternion final
	{
	public:
		float x;
		float y;
		float z;
		float w;
		static const Quaternion Identity;

		Quaternion();
		explicit Quaternion(float x, float y, float z, float w);
		explicit Quaternion(const Vector3& axis, float angle);

		// 型変換
		inline Quaternion(DirectX::XMVECTOR v)
		{
			DirectX::XMFLOAT4 tmp;
			DirectX::XMStoreFloat4(&tmp, v);
			this->x = tmp.x;
			this->y = tmp.y;
			this->z = tmp.z;
			this->w = tmp.w;
		}
		inline static DirectX::XMVECTOR CastXMVECTOR(Quaternion q)
		{
			DirectX::XMVECTOR tmp = DirectX::XMVectorSet(q.x, q.y, q.z, q.w);
			return tmp;
		}
		
		void Set(float x, float y, float z, float w);
		void Conjugate();
		float LengthSq() const;
		float Length() const;
		void Normalize();
		static Quaternion Normalize(const Quaternion& q);
		static Quaternion Lerp(const Quaternion& a, const Quaternion& b, float f);
		static float Dot(const Quaternion& a, const Quaternion& b);
		static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float f);
		// Quaternionの合成
		static Quaternion Concatenate(const Quaternion& q, const Quaternion& p);
	};
#pragma endregion Quaternionクラス

#pragma region Matrix

	class Matrix final
	{
	public:
		static DirectX::XMMATRIX MatrixScaling(Vector3  Scale);
		static DirectX::XMMATRIX MatrixRotationQuatrnion(Quaternion Quaternion);
		static DirectX::XMMATRIX MatrixRotationQuatrnionRollPitchYaw(Quaternion Quaternion);
		static DirectX::XMMATRIX MatrixRotationRollPitchYaw(Vector3 Rotation);
		static DirectX::XMMATRIX MatrixTranslation(Vector3 Position);
	};
#pragma endregion Matrixクラス
}

// 便利なやつ
namespace myLib 
{
#pragma region TexCoord_List
	//namespace Texcoord
	//{
	//		const float div8[9] = { 0.0f, 0.125f, 0.25f, 0.375f, 0.5f, 0.625f, 0.75f, 0.875f, 1.0f };
	//		const float div4[5] = { 0.0f, 0.25f, 0.5f, 0.75f, 1.0f };
	//		const float div2[3] = { 0.0f, 0.5f, 1.0f };
	//};
#pragma endregion テクスチャ座標
#pragma region Random&inlineMethod
	// XorShiftを使ったランダム生成クラス
	class Random final
	{
	public:
		Random(const Random&) = delete;
		Random& operator=(const Random&) = delete;
		Random(Random&&) = delete;
		Random& operator=(Random&&) = delete;

		// Min～Max の範囲の乱数。
		inline static int Rand_R(const int Min, const int Max)
		{
			return (rand() % (Max - Min)) + Min;
		}

		// 0.0～1.0 の範囲の実数乱数にする。
		inline static float GetRandomXORf()
		{
			static Random ins;
			unsigned int t = (ins.xorRandomSeedX ^ (ins.xorRandomSeedX << 11));
			ins.xorRandomSeedX = ins.xorRandomSeedY;
			ins.xorRandomSeedY = ins.xorRandomSeedZ;
			ins.xorRandomSeedZ = ins.xorRandomSeedW;
			ins.xorRandomSeedW = (ins.xorRandomSeedW ^ (ins.xorRandomSeedW >> 19)) ^ (t ^ (t >> 8));

			return float(ins.xorRandomSeedW % 10000) / float(10000);
		}

		// -1.0～+1.0 の範囲の実数乱数にする。
		inline static float GetRandomXOR()
		{
			return 2.0f * GetRandomXORf() - 1.0f;
		}

		//半径radius円内の点をランダムに取得
		inline static void InsideUnitSpheref(float* x, float* y, float radius)
		{
			const float r = GetRandomXORf() * DirectX::XM_2PI;
			const float s = radius * sqrtf(GetRandomXORf());
			*x = s * cosf(r) + radius;
			*y = s * sinf(r) + radius;
		}

	private:
		inline Random()
		{
			srand((unsigned int)time(NULL));
			CreateInitNumber();
		}

		inline ~Random()
		{

		}

		inline void CreateInitNumber()
		{
			unsigned int seed = rand();
			if (seed == 0)
			{
				seed += 11;
			}

			xorRandomSeedW = seed;
			xorRandomSeedX = (seed << 16) + (seed >> 16);
			xorRandomSeedY = xorRandomSeedW + xorRandomSeedX;
			xorRandomSeedZ = xorRandomSeedX ^ xorRandomSeedY;
		}

		// 2バイトか4バイトの符号なし整数
		unsigned int xorRandomSeedX;
		unsigned int xorRandomSeedY;
		unsigned int xorRandomSeedZ;
		unsigned int xorRandomSeedW;
	};
#pragma endregion XorShiftを使ったRandomクラスと関数

#pragma region DoOece
	#define CAT_(a,b) a##b
	#define CAT(a,b) CAT_(a,b)
	// 一度だけ実行
	#define DoOnce(function) static bool CAT(DO_ONCE_,__LINE__)=[](){function();return true;}();
	// DoOnceの応用。関数をN回実行する
	#define DoTimes(function, n) static int CAT(DO_ONCE_CTR,__LINE__)=n;if(CAT(DO_ONCE_CTR,__LINE__)>0){function();CAT(DO_ONCE_CTR,__LINE__) --;*}
/*
	class Doonce final
	{
	public:
		Doonce() : m_Flag(false){ }
		~Doonce() { m_Flag = false; }
		template<typename T, typename Return>
		void Run(std::function<T*(Return)> func)
		{
			if (!m_Flag)
			{
				func();
				m_Flag = false;
			}
		}
		void Reset()
		{
			if (m_Flag)
			{
				m_Flag = false;
			}
		}
	private:
		bool m_Flag;
	};
	*/
#pragma endregion DoOnce

#pragma region Timeline 
	// タイムライン　２点間のみ
	class Timeline final
	{
	public:
		Timeline() = delete;
		// 2点と変化率の設定
		Timeline(float Start, float End, float Rate);
		
		// 頭から
		void Start(float& v);
		// 後ろから
		void Reverce(float& v);

		// 変化率の設定
		void SetRate(float t);
	private:
		// ２区間
		boost::numeric::interval<float> m_Interval;
		// 変化率
		float m_Rate;
	};
#pragma endregion Timelineクラス

#pragma region SmartPtr
	template<typename T>
	class SmartPtr final
	{
	public:
#pragma region コンストラクタ＆デストラクタ
		// デフォルトコンストラクタ
		explicit SmartPtr(T* p = nullptr, uint32_t add = 0)
		{
			m_pRefCount = new uint32_t;
			*m_pRefCount = add;
			m_Ptr = new T*;
		}

		// コピーコンストラクタ
		SmartPtr(const SmartPtr<T>& p)
		{
			m_pRefCount = p.m_pRefCount;
			m_Ptr = p.m_Ptr;
			this->Add();
		}

		// コピーコンストラクタ(暗黙的アップキャスト)
		template<typename T2>
		SmartPtr(SmartPtr<T2>& p)
		{
			// ダブルポインタのコピー
			m_pRefCount = p.GetReference();
			m_Ptr = (T**)p.Getdoule();

			// 型のチェックコピー
			*m_Ptr = p.Get();
			this->Add();
		}

		// コピーコンストラクタ(null)
		SmartPtr(const std::nullptr_t null)
		{
			m_pRefCount = new uint32_t;
			*m_pRefCount = 0;
			m_Ptr = new T*;
			m_Ptr = nullptr;
			this->Add();
		}

		// 参照カウンタの増加
		inline void Add()
		{
			(*m_pRefCount)++;
		}
		// 参照カウンタの減少
		inline void Release()
		{
			if (--(*m_pRefCount) == 0)
			{
				delete *m_Ptr;
				delete m_Ptr;
				delete m_pRefCount;
			}
		}

		// デストラクタ
		~SmartPtr()
		{
			this->Release();
		}
#pragma endregion コンストラクタ＆デストラクタ

#pragma region メンバ関数
		// セッター
		void Set(T* p = nullptr, uint32_t add = 0)
		{
			this->Release();
			m_pRefCount = new uint32_t;
			*m_pRefCount = add;
			m_Ptr = new T*;
			p ? *m_Ptr = p : *m_Ptr = nullptr;
			this->Add();
		}

		// ゲッター
		T* Get() { return *m_Ptr; }
		T** Getdoule() { return m_Ptr; }
		// 参照カウンタへのポインタ
		uint32_t* GetReference() { return m_pRefCount; }

		// ダウンキャスト
		template<typename T2>
		bool Cast(SmartPtr<T2>& p)
		{
			// 引数のポインタが自分の登録しているポインタにダウンキャストが可能ならダウンキャストコピー
			T* cast = dynamic_cast<T*>(p.Get());
			if (cast)
			{
				// ダウンキャスト成功時の処理
				this->Release(); // 既存の参照カウンタを１つ減らす
				// ポインタとカウンタを共有
				m_Ptr = (T**)p.Getdoule();
				m_pRefCount = cast;
				m_pRefCount = p.GetReference();
				// カウンタを追加
				this->Add();
				return true;
			}
			return false; // 失敗
		}

		// 交換
		void Swap(SmartPtr<T> &p)
		{
			T* tmp = p.Get();
			*p.m_Ptr = *m_Ptr;
			*m_Ptr = tmp;
		}
#pragma endregion メンバ関数

#pragma region 演算子のオーバーロード
		// コピー
		SmartPtr<T>& operator= (const SmartPtr<T>& p)
		{
			// 自分自身の代入はしない
			if (*p.m_Ptr == *m_Ptr) { return *this; }
			this->Release();
			// 相手のポインタをコピー
			m_pRefCount = p.m_pRefCount;
			m_Ptr = p.m_Ptr;
			this->Add();
		}

		// アップキャスト
		template<typename T2>
		SmartPtr<T>& operator=(SmartPtr<T2>& p)
		{
			// 自分自身の代入はしない
			if (*p.m_Ptr == *m_Ptr) { return *this; }
			this->Release();
			// 相手のポインタをコピー
			m_pRefCount = p.GetReference();
			m_Ptr = (T**)p.Getdoule();
			// 型をチェックコピー
			*m_Ptr = p.Get();
			this->Add();
			return *this;
		}

		// nullptr代入
		SmartPtr<T>& operator= (const std::nullptr_t null)
		{
			this->Release();
			m_pRefCount = new uint32_t;
			m_Ptr = new T*;
			*m_Ptr = nullptr;
			return *this;
		}

		// * 間接代入
		T& operator*() { return **m_Ptr; }

		// -> メンバ選択演算子
		T* operator->() { return *m_Ptr; }

		// == 比較演算子
		bool operator==(T* val)
		{
			if (*m_Ptr == val)
			{
				return true;
			}
			return false;
		}
		// != 比較演算子
		bool operator!=(T* val)
		{
			if (*m_Ptr == val)
			{
				return true;
			}
			return false;
		}
#pragma endregion 演算子のオーバーロード

	private:
		T** m_Ptr; // T型のオブジェクトのダブルポインタ
		uint32_t* m_pRefCount; // 参照カウンタ		
	};
#pragma endregion SmartPtrクラス
}