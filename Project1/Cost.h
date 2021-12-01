/*--------------------------------------------------------------

	[Cost.h]
	Author : 出合翔太

	戦車のコストを描画する

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

