/*-------------------------------------------------------------
	
	[Utility.h]
	Author : 出合翔太

--------------------------------------------------------------*/
#pragma once
#include <windows.h>
#include <assert.h> // エラー処理
#include <iostream>

// ランタイムエラーマクロ
#define STRINGFY(s)  #s
#define TO_STRING(x) STRINGFY(x)
#define FILE_PREFIX __FILE__ "(" TO_STRING(__LINE__) "): " 
#define ThrowIfFailed(hr, msg) Utility::CheckResultCode( hr, FILE_PREFIX msg)

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
