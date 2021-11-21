/*------------------------------------------------------------

	[Playervehicle.h]
	Author : �o���đ�

-------------------------------------------------------------*/
#pragma once
#include "Pawn.h"

class Player final : public Pawn
{
public:
	Player();
	~Player();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void Respawn(const D3DXVECTOR3& pos)override;
	void UseSkill();
private:
	void OnCollision()override;
	void OnSound(); //	�T�E���h�̐ݒ�
	class Resource& m_Resource;
	float m_Volume = 0.0f;
	bool m_Audioplay = false;
	bool m_HitWall = false;
};

