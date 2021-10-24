/*------------------------------------------------------------
	
	[Bg.h]
	Author : èoçá„ƒëæ

-------------------------------------------------------------*/
#pragma once
#include "Actor.h"

class Bg : public Actor
{
public:
	Bg();
	virtual ~Bg();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	const Math::Vector2& GetSize() const;
	const float GetWidth() const;
	const float GetHeight() const;
protected:	
	Math::Vector2 m_Size;
	std::unique_ptr<class Renderer2D> m_Renderer2D;
	class Resource& m_Resource;
	class Graphics& m_Graphics;
};

