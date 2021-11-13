/*-----------------------------------------------------------
	
	[Turret.h]
	Author : �o���đ�

	��Ԃ̖C��

------------------------------------------------------------*/
#pragma once
#include "Parts.h"

class Turret final : public Parts
{
public:
	Turret() = delete;
	Turret(const std::string& Tag);
	~Turret();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void UpdateMatrix(const D3DXMATRIX& ParentMatirx)override;
};

