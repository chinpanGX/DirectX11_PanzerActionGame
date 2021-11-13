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

#pragma region Matrix
	class Matrix final
	{
	public:
		static void MatrixScaling(D3DXMATRIX* m, D3DXVECTOR3 Scale);
		static void MatrixRotationRollPitchYaw(D3DXMATRIX* m, D3DXVECTOR3 Rotation);
		static void MatrixTranslation(D3DXMATRIX* m, D3DXVECTOR3 Position);
	};
#pragma endregion Matrixクラス
}

// 便利なやつ
namespace myLib 
{
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