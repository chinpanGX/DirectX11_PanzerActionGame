/*-----------------------------------------------------------

	[Effect.h]
	Author : �o���đ�

	�G�t�F�N�g�̊��N���X

-------------------------------------------------------------*/
#pragma once
#include "Actor.h"

class Effect : public Actor
{
public:
	Effect();
	// �e�N�X�`�����W��ݒ�
	Effect(D3DXVECTOR2 TexMin, D3DXVECTOR2 TexMax);
	virtual ~Effect();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
protected:
	// Map��Unmap������@
	void MapAndUnmap(float Pos_x, float Pos_y); // ����(�e�N�X�`�����W��x,y)
	uint32_t GetFrame() const { return m_Frame; }
	class Resource& m_Resource;
	class Graphics& m_Graphics;
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	uint32_t m_Frame;
};

