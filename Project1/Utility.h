/*-------------------------------------------------------------
	
	[Utility.h]
	Author : 出合翔太

--------------------------------------------------------------*/
#pragma once

#include <windows.h>
#include <assert.h> // エラー処理
#include <iostream>
#include <typeinfo>
#include <string>
#include <cstdio>

// ランタイムエラーマクロ
#define STRINGFY(s)  #s
#define TO_STRING(x) STRINGFY(x)
#define FILE_PREFIX __FILE__ "(" TO_STRING(__LINE__) "): " 
#define ThrowIfFailed(hr, msg) Utility::CheckResultCode( hr, FILE_PREFIX msg)

#ifdef _DEBUG
#   define MyOutputDebugString( str, ... ) \
      { \
        TCHAR c[256]; \
        _stprintf( c, str, __VA_ARGS__ ); \
        OutputDebugString( c ); \
      }
#else
#    define MyOutputDebugString( str, ... ) // 空実装
#endif

#if 0
// nullチェック
template<typename T>
static void nullcheck(const T* object)
{
	// オブジェクトがnullのとき、エラー処理
	if (!object)
	{
		// クラス名を取得する
		const type_info& id = typeid(object);
		std::string name = id.name();
		std::domain_error(name + "nullpointer");
	}
}
#endif

namespace Utility
{
	class Exception final : public std::runtime_error
	{
	public:
		inline Exception(const std::string& msg) : std::runtime_error(msg.c_str()) {}
	};

	inline void CheckResultCode(HRESULT hr, const std::string& errorMsg)
	{
		if (FAILED(hr))
		{
			throw Exception(errorMsg);
		}
	}
}
