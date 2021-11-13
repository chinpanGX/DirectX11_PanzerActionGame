/*--------------------------------------------------------------

	[myLib.h]
	Author : �o���đ��@

	����֗̕��Ȃ��̂��܂Ƃ߂�

	Math : �Z�p���C�u����
	myLib : �֗��ȃN���X�A�֐�

---------------------------------------------------------------*/
#pragma once
#include "stdafx.h"
#include <math.h>
#include <time.h>
#include <functional>
#include <boost/numeric/interval.hpp>
#include <boost/numeric/interval/io.hpp>
#include <typeinfo>

// �Z�p���C�u����
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
#pragma endregion �v�Z�֐�

#pragma region Matrix
	class Matrix final
	{
	public:
		static void MatrixScaling(D3DXMATRIX* m, D3DXVECTOR3 Scale);
		static void MatrixRotationRollPitchYaw(D3DXMATRIX* m, D3DXVECTOR3 Rotation);
		static void MatrixTranslation(D3DXMATRIX* m, D3DXVECTOR3 Position);
	};
#pragma endregion Matrix�N���X
}

// �֗��Ȃ��
namespace myLib 
{
#pragma region Random&inlineMethod
	// XorShift���g���������_�������N���X
	class Random final
	{
	public:
		Random(const Random&) = delete;
		Random& operator=(const Random&) = delete;
		Random(Random&&) = delete;
		Random& operator=(Random&&) = delete;

		// Min�`Max �͈̗̔͂����B
		inline static int Rand_R(const int Min, const int Max)
		{
			return (rand() % (Max - Min)) + Min;
		}

		// 0.0�`1.0 �͈̔͂̎��������ɂ���B
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

		// -1.0�`+1.0 �͈̔͂̎��������ɂ���B
		inline static float GetRandomXOR()
		{
			return 2.0f * GetRandomXORf() - 1.0f;
		}

		//���aradius�~���̓_�������_���Ɏ擾
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

		// 2�o�C�g��4�o�C�g�̕����Ȃ�����
		unsigned int xorRandomSeedX;
		unsigned int xorRandomSeedY;
		unsigned int xorRandomSeedZ;
		unsigned int xorRandomSeedW;
	};
#pragma endregion XorShift���g����Random�N���X�Ɗ֐�

#pragma region DoOece
	#define CAT_(a,b) a##b
	#define CAT(a,b) CAT_(a,b)
	// ��x�������s
	#define DoOnce(function) static bool CAT(DO_ONCE_,__LINE__)=[](){function();return true;}();
	// DoOnce�̉��p�B�֐���N����s����
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
	// �^�C�����C���@�Q�_�Ԃ̂�
	class Timeline final
	{
	public:
		Timeline() = delete;
		// 2�_�ƕω����̐ݒ�
		Timeline(float Start, float End, float Rate);
		
		// ������
		void Start(float& v);
		// ��납��
		void Reverce(float& v);

		// �ω����̐ݒ�
		void SetRate(float t);
	private:
		// �Q���
		boost::numeric::interval<float> m_Interval;
		// �ω���
		float m_Rate;
	};
#pragma endregion Timeline�N���X

#pragma region SmartPtr
	template<typename T>
	class SmartPtr final
	{
	public:
#pragma region �R���X�g���N�^���f�X�g���N�^
		// �f�t�H���g�R���X�g���N�^
		explicit SmartPtr(T* p = nullptr, uint32_t add = 0)
		{
			m_pRefCount = new uint32_t;
			*m_pRefCount = add;
			m_Ptr = new T*;
		}

		// �R�s�[�R���X�g���N�^
		SmartPtr(const SmartPtr<T>& p)
		{
			m_pRefCount = p.m_pRefCount;
			m_Ptr = p.m_Ptr;
			this->Add();
		}

		// �R�s�[�R���X�g���N�^(�ÖٓI�A�b�v�L���X�g)
		template<typename T2>
		SmartPtr(SmartPtr<T2>& p)
		{
			// �_�u���|�C���^�̃R�s�[
			m_pRefCount = p.GetReference();
			m_Ptr = (T**)p.Getdoule();

			// �^�̃`�F�b�N�R�s�[
			*m_Ptr = p.Get();
			this->Add();
		}

		// �R�s�[�R���X�g���N�^(null)
		SmartPtr(const std::nullptr_t null)
		{
			m_pRefCount = new uint32_t;
			*m_pRefCount = 0;
			m_Ptr = new T*;
			m_Ptr = nullptr;
			this->Add();
		}

		// �Q�ƃJ�E���^�̑���
		inline void Add()
		{
			(*m_pRefCount)++;
		}
		// �Q�ƃJ�E���^�̌���
		inline void Release()
		{
			if (--(*m_pRefCount) == 0)
			{
				delete *m_Ptr;
				delete m_Ptr;
				delete m_pRefCount;
			}
		}

		// �f�X�g���N�^
		~SmartPtr()
		{
			this->Release();
		}
#pragma endregion �R���X�g���N�^���f�X�g���N�^

#pragma region �����o�֐�
		// �Z�b�^�[
		void Set(T* p = nullptr, uint32_t add = 0)
		{
			this->Release();
			m_pRefCount = new uint32_t;
			*m_pRefCount = add;
			m_Ptr = new T*;
			p ? *m_Ptr = p : *m_Ptr = nullptr;
			this->Add();
		}

		// �Q�b�^�[
		T* Get() { return *m_Ptr; }
		T** Getdoule() { return m_Ptr; }
		// �Q�ƃJ�E���^�ւ̃|�C���^
		uint32_t* GetReference() { return m_pRefCount; }

		// �_�E���L���X�g
		template<typename T2>
		bool Cast(SmartPtr<T2>& p)
		{
			// �����̃|�C���^�������̓o�^���Ă���|�C���^�Ƀ_�E���L���X�g���\�Ȃ�_�E���L���X�g�R�s�[
			T* cast = dynamic_cast<T*>(p.Get());
			if (cast)
			{
				// �_�E���L���X�g�������̏���
				this->Release(); // �����̎Q�ƃJ�E���^���P���炷
				// �|�C���^�ƃJ�E���^�����L
				m_Ptr = (T**)p.Getdoule();
				m_pRefCount = cast;
				m_pRefCount = p.GetReference();
				// �J�E���^��ǉ�
				this->Add();
				return true;
			}
			return false; // ���s
		}

		// ����
		void Swap(SmartPtr<T> &p)
		{
			T* tmp = p.Get();
			*p.m_Ptr = *m_Ptr;
			*m_Ptr = tmp;
		}
#pragma endregion �����o�֐�

#pragma region ���Z�q�̃I�[�o�[���[�h
		// �R�s�[
		SmartPtr<T>& operator= (const SmartPtr<T>& p)
		{
			// �������g�̑���͂��Ȃ�
			if (*p.m_Ptr == *m_Ptr) { return *this; }
			this->Release();
			// ����̃|�C���^���R�s�[
			m_pRefCount = p.m_pRefCount;
			m_Ptr = p.m_Ptr;
			this->Add();
		}

		// �A�b�v�L���X�g
		template<typename T2>
		SmartPtr<T>& operator=(SmartPtr<T2>& p)
		{
			// �������g�̑���͂��Ȃ�
			if (*p.m_Ptr == *m_Ptr) { return *this; }
			this->Release();
			// ����̃|�C���^���R�s�[
			m_pRefCount = p.GetReference();
			m_Ptr = (T**)p.Getdoule();
			// �^���`�F�b�N�R�s�[
			*m_Ptr = p.Get();
			this->Add();
			return *this;
		}

		// nullptr���
		SmartPtr<T>& operator= (const std::nullptr_t null)
		{
			this->Release();
			m_pRefCount = new uint32_t;
			m_Ptr = new T*;
			*m_Ptr = nullptr;
			return *this;
		}

		// * �Ԑڑ��
		T& operator*() { return **m_Ptr; }

		// -> �����o�I�����Z�q
		T* operator->() { return *m_Ptr; }

		// == ��r���Z�q
		bool operator==(T* val)
		{
			if (*m_Ptr == val)
			{
				return true;
			}
			return false;
		}
		// != ��r���Z�q
		bool operator!=(T* val)
		{
			if (*m_Ptr == val)
			{
				return true;
			}
			return false;
		}
#pragma endregion ���Z�q�̃I�[�o�[���[�h

	private:
		T** m_Ptr; // T�^�̃I�u�W�F�N�g�̃_�u���|�C���^
		uint32_t* m_pRefCount; // �Q�ƃJ�E���^		
	};
#pragma endregion SmartPtr�N���X
}