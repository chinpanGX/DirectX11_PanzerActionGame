/*------------------------------------------------------------
	
	[GrassField.h]
	Author : 出合翔太

	Grassオブジェクトをまとめる

--------------------------------------------------------------*/
#pragma once
#include "Actor.h"

class GrassField final : public Actor
{
public:
	GrassField();
	~GrassField();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};

