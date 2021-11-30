/*-------------------------------------------------------------
	
	[MiniMap.h]
	Author : �o���đ�

	�~�j�}�b�v�̕\��

--------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include <memory>
#include <vector>

// �v���C���[�̃A�C�R��
class PlayerIcon final
{
public:
	PlayerIcon();
	~PlayerIcon();
	// param name
	// pos = "�`��ʒu", size = "�`��T�C�Y", rot = "��]"
	void Draw(D3DXVECTOR2 pos, D3DXVECTOR2 size, float rot);
private:	
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	Graphics& m_Graphics;
	Resource& m_Resource;
};

// �~�j�}�b�v
class Enemy;
class Player;
class Renderer2D;
class MiniMap final : public DefaultObject
{
public:
	MiniMap();
	~MiniMap();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:
	std::unique_ptr<Renderer2D> m_Bg;
	std::unique_ptr<Renderer2D> m_Map;
	std::unique_ptr<Renderer2D> m_Icon;
	std::unique_ptr<PlayerIcon> m_PlayerIcon;
	
	std::vector<Supply*> m_SupplyList;
	Enemy* m_Enemy;
	Player* m_Player;


	D3DXVECTOR2 m_PlayerPosition;
	D3DXVECTOR2 m_EnemyPosition;

	D3DXVECTOR2 m_Position; // �~�j�}�b�v�̈ʒu
	float m_MapSize;		// �~�j�}�b�v�̑傫��
	float m_Shrink;			// ���ۂ̃}�b�v�ɑ΂��ă~�j�}�b�v���k������{��
};
