/*--------------------------------------------------------------
	
	[PanzerList.h]
	Author : èoçá„ƒëæ

	êÌé‘ÇÃÉäÉXÉg

---------------------------------------------------------------*/
#pragma once
#include "Vehicle.h"

class Tiger final : public Vehicle
{
public:
	Tiger();
	~Tiger();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};

class Centurion final : public Vehicle
{
public:
	Centurion();
	~Centurion();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};

class Patton : public Vehicle
{
public:
	Patton();
	~Patton();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};

class T_34_85 : public Vehicle
{
public:
	T_34_85();
	~T_34_85();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};

class IV_H final : public Vehicle
{
public:
	IV_H();
	~IV_H();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};

class Sherman final : public Vehicle
{
public:
	Sherman();
	~Sherman();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};