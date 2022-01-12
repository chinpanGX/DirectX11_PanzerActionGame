/*-------------------------------------------------------------

	[Supply.h]
	Author : �o���đ�

	�⋋�n�_

--------------------------------------------------------------*/
#pragma once
#include "StageObject.h"
#include "Effect.h"

// �⋋�͈͂������p�[�e�B�N��
class Renderer2D;
class CircleParticle final : public Actor
{
public:
	CircleParticle();
	~CircleParticle();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void Generate(float x, float z);
private:
	D3DXVECTOR4 m_Color;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	class Resource& m_Resource;
	class Graphics& m_Graphics;
};

class Supply final : public StageObject
{
public:
	Supply();
	~Supply();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:
	std::vector<CircleParticle*> m_Particles;
	float m_Angle;
	float m_Radius;
};
