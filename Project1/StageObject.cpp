/*-------------------------------------------------------------
	
	[StageObejct.cpp]
	Author : èoçá„ƒëæ

--------------------------------------------------------------*/
#include "Engine.h"
#include "Resource.h"
#include "StageObject.h"

StageObject::StageObject() : m_Resource(*Engine::Get().GetResource())
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

Resource & StageObject::GetResource() const
{
	return m_Resource;
}

/*
	setter/getter
*/
void StageObject::SetRadius(float Radius)
{
	m_Radius = Radius;
}

float StageObject::GetRadius() const
{
	return m_Radius;
}
