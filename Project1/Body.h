/*-----------------------------------------------------------
	
	[TankBody.h]
	Author : �o���đ�

	��Ԃ̎ԑ�

------------------------------------------------------------*/
#pragma once
#include "Parts.h"

class Body final : public Parts
{
public:
	Body() = delete;
	Body(const std::string& Tag);
	~Body();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void UpdateMatrix(const D3DXMATRIX& ParentMatirx)override;
};

