/*-----------------------------------------------------------
	
	[MainGun.h]
	Author : o‡ãÄ‘¾

	íÔ‚Ìå–C

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
	void UpdateMatrix(const DirectX::XMFLOAT4X4& ParentMatirx)override;
};

