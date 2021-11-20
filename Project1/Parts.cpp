/*--------------------------------------------------------------
	
	[Parts.cpp]
	Author : èoçá„ƒëæ

---------------------------------------------------------------*/
#include "Engine.h"
#include "Resource.h"
#include "Graphics.h"
#include "Parts.h"

Parts::Parts(const std::string & Tag) : m_Tagname(Tag), m_Resource(*Engine::Get().resource()), m_Graphics(*Engine::Get().graphics())
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

Resource & Parts::resource() const
{
	return m_Resource;
}

Graphics & Parts::graphics() const
{
	return m_Graphics;
}
