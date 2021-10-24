/*-------------------------------------------------------------
	
	[Loader.h]
	Author : èoçá„ƒëæ

--------------------------------------------------------------*/
#pragma once
#include "stdafx.h"
#include "Graphics.h"
#include <string>
#include <unordered_map>

class Loader
{
public:
	virtual void Load(const std::string& name) = 0;
protected:
	template< typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
};

