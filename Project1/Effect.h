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
	Effect(D3DXVECTOR2 texMin, D3DXVECTOR2 texMax);
	virtual ~Effect();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
protected:
	// Map��Unmap������@
	void MapAndUnmap(float x, float y); // ����(�e�N�X�`�����W��x,y)
	uint32_t GetFrame() const { return m_Frame; }
	class Resource& m_Resource;
	class Graphics& m_Graphics;
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	uint32_t m_Frame;
};

