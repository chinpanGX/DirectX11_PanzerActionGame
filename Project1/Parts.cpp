/*--------------------------------------------------------------
	
	[Parts.cpp]
	Author : èoçá„ƒëæ

---------------------------------------------------------------*/
#include "Engine.h"
#include "Resource.h"
#include "Graphics.h"
#include "Parts.h"

Parts::Parts(const std::string & Tag) : m_Tagname(Tag), m_Resource(*Engine::Get().GetResource()), m_Graphics(*Engine::Get().GetGraphics())
{
}

const D3DXMATRIX & Parts::GetWorldMatrix() const
{
	return m_WorldMatrix;
}

const std::string & Parts::tag() const
{
	return m_Tagname;
}

Resource & Parts::GetResource() const
{
	return m_Resource;
}

Graphics & Parts::GetGraphics() const
{
	return m_Graphics;
}
