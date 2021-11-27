/*------------------------------------------------------------

	[Playervehicle.h]
	Author : �o���đ�

-------------------------------------------------------------*/
#pragma once
#include "Pawn.h"

namespace PlayerUi 
{ 
	class DrawSkill; 
	class Reload; 
}
class Graphics;
class Resource;
class GameCommand;
class GameCamera;
class Enemy;
class Pause;
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
	void Shot();
private:
	void OnCollision()override;
	void OnSound(); //	�T�E���h�̐ݒ�
	

	std::vector<Enemy*> m_EnemyList;
	
	D3DXVECTOR4 m_Param;
	GameCommand* m_Command;
	GameCamera* m_Camera;
	Pause* m_Pause;
	PlayerUi::DrawSkill* m_DrawSkill;
	PlayerUi::Reload* m_Reload;
	Resource& m_Resource;
	Graphics& m_Graphics;

	float m_Volume = 0.0f;
	bool m_Audioplay = false;
	bool m_HitWall = false;
};

