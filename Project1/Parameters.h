/*--------------------------------------------------------------
	
	[Parameters.h]
	Author : �o���đ�

	��Ԃ̃p�����[�^�̕\��

---------------------------------------------------------------*/
#pragma once
#include "myLib.h"
#include "Bg.h"

// �p�����[�^�\��
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
