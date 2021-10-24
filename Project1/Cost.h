/*--------------------------------------------------------------

	[Cost.h]
	Author : 出合翔太

	戦車のコストを描画する

---------------------------------------------------------------*/
#pragma once
#include "IDrawNumber.h"
 
class Cost final : public IDrawNumber
{ 
public:
	Cost();
	~Cost();
	void Draw(int32_t n)override;
private:
	float m_Cost;
};

