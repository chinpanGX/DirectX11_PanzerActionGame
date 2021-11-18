/*-------------------------------------------------------------
	
	[StageObejct.cpp]
	Author : èoçá„ƒëæ

--------------------------------------------------------------*/
#include "Engine.h"
#include "Resource.h"
#include "StageObject.h"

StageObject::StageObject() : m_Resource(*Engine::Get().resource())
{
}

StageObject::~StageObject()
{
}

void StageObject::Begin()
{
}

void StageObject::Update()
{
}

void StageObject::Event()
{
}

void StageObject::Draw()
{
}

Resource & StageObject::resource() const
{
	return m_Resource;
}

/*
	setter/getter
*/
void StageObject::redius(float r)
{
	m_Radius = r;
}

float StageObject::radius() const
{
	return m_Radius;
}
