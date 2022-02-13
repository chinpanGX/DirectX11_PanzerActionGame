/*--------------------------------------------------------------
	
	[Parameters.h]
	Author : 出合翔太

	パラメータの表示

---------------------------------------------------------------*/
#pragma once
#include "myLib.h"
#include "Bg.h"

// パラメータ表示
class Parameters final 
{
public:
	Parameters();
	~Parameters();
	void Draw(float Param, const D3DXVECTOR2& Pos);
private:
	std::unique_ptr<class Render> m_Render;
	std::unique_ptr<class Renderer2D> m_Bg;
};
