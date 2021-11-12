/*-----------------------------------------------------------
	
	[MainGun.h]
	Author : �o���đ�

	��Ԃ̎�C

------------------------------------------------------------*/
#pragma once
#include "Parts.h"

class MainGun final : public Parts
{
public:
	MainGun() = delete;
	MainGun(const std::string& Tag);
	~MainGun();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void UpdateMatrix(const D3DXMATRIX& ParentMatirx)override;
};

