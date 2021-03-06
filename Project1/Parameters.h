/*--------------------------------------------------------------
	
	[Parameters.h]
	Author : 出合翔太

	戦車のパラメータの表示

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
	void Draw(float Param, const D3DXVECTOR2& Position);
private:
	std::unique_ptr<class RenderGage> m_Render;
	std::unique_ptr<class Renderer2D> m_Bg;
};
