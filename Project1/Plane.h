/*------------------------------------------------------------

	[Plane.h]
	Author : �o���đ�

	���I�u�W�F�N�g

--------------------------------------------------------------*/
#pragma once
#include "StageObject.h"
#include "Graphics.h"

namespace
{
	// �u���b�N�̐�
	const uint32_t g_BlockNum = 100;									
}

class Plane final : public StageObject
{
public:
	Plane();
	~Plane();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:	
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_IndexBuffer;
	Vertex3D m_Vertex[g_BlockNum + 1][g_BlockNum + 1];
	Graphics& m_Graphics;
};

class GameWorld final : public StageObject
{
public:
	GameWorld();
	~GameWorld();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:
	void GenerateHeight();

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_IndexBuffer;
	Vertex3D m_Vertex[g_BlockNum + 1][g_BlockNum + 1];
	Graphics& m_Graphics;
};
