/*--------------------------------------------------------------

	[Cost.h]
	Author : �o���đ�

	��Ԃ̃R�X�g��`�悷��

---------------------------------------------------------------*/
#pragma once
#include "DrawNumber.h"
 
class Cost final : public DrawNumber
{ 
public:
	Cost();
	~Cost();
	void Draw(int32_t value)override;
private:
	float m_Cost;
};

