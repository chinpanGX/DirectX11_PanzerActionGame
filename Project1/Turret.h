/*-----------------------------------------------------------
	
	[Turret.h]
	Author : o‡ãÄ‘¾

	íÔ‚Ì–C‘ä

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
	void UpdateMatrix(const DirectX::XMFLOAT4X4& ParentMatirx)override;
};

