/*--------------------------------------------------------------
	
	[Shadow.h]
	Author : èoçá„ƒëæ

----------------------------------------------------------------*/
#pragma once
#include "Effect.h"

class Shadow : public Actor
{
public:
	Shadow();
	~Shadow();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	class Resource& m_Resource;
	class Graphics& m_Graphics;
};

