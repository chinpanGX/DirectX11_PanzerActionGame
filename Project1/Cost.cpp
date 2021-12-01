/*--------------------------------------------------------------

	[Cost.cpp]
	Author : �o���đ�

	��Ԃ̃R�X�g��`�悷��

---------------------------------------------------------------*/
#include "Engine.h"
#include "Graphics.h"
#include "Resource.h"
#include "Renderer2D.h"
#include "Cost.h"

Cost::Cost() : DrawNumber(64.0f, 2)
{
}

Cost::~Cost()
{
}

void Cost::Draw(int32_t value)
{
	for (int32_t i = 0; i < Getdigit(); ++i)
	{
		int num = value % 10;
		value /= 10;
		NumberDraw(D3DXVECTOR2(1650.0f + ((GetSize() - 20.0f) * (Getdigit() - (i + 1))), 200.0f), num);
	}
}
