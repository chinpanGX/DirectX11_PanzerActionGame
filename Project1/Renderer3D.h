/*----------------------------------------------------------

	[Renderer3D.h]
	Author : �o���đ�

-----------------------------------------------------------*/
#pragma once
#include "myLib.h"

class Graphics;
class Renderer3D final
{
public:
	Renderer3D() = delete;
	Renderer3D(Graphics& Graphics, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);
	~Renderer3D();
	void Update(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);
	void UpdeteMatrix(); // �s��v�Z
	void Draw();
	
	//  Distancee/���_�Ԃ̋���  untiling / �e�N�X�`���̖��x�̔{��, texcoord / �e�N�X�`�����W,
	// X�[�y�̕��ʂ̃|���S���̍쐬
	void CreatePlane(float Distance = 10.0f, int UvTiling = 1, D3DXVECTOR2 Tex = D3DXVECTOR2(1.0f, 1.0f)); 
	// �w�[�x�̕ǂ̕��ʃ|���S��
	void CreateWall(float Distance = 10.0f, int UvTiling = 1, D3DXVECTOR2 Tex = D3DXVECTOR2(1.0f, 1.0f)); 
private:
	Graphics& m_Graphics;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Scale;
};

