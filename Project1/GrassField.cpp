/*------------------------------------------------------------

	[GrassField.cpp]
	Author : 出合翔太

	Grassオブジェクトをまとめる

--------------------------------------------------------------*/
#include "Application.h"
#include "Engine.h"
#include "Stage.h"
#include "Grass.h"
#include "GrassField.h"

GrassField::GrassField()
{
	const int32_t GrassMax = 10;
	for (int32_t z = 0; z < GrassMax; ++z)
	{
		for (int32_t x = 0; x < GrassMax; ++x)
		{
			Engine::Get().GetApplication()->GetScene()->AddGameObject<Grass>(LAYER_3D_STAGE)->GetTransform().position(3.0f * x, -1.0f, 3.0f * z);
		}
	}
}

GrassField::~GrassField()
{
}

void GrassField::Begin()
{
}

void GrassField::Update()
{
	
}

void GrassField::Event()
{
}

void GrassField::Draw()
{
	
}
