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
class Supply;
class PlayerReload;
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

	void ReplenishBullets();	// �e��⋋���� 
	bool isBulletsUpperLimit(); // �e�̐���������ǂ���
	bool enterSupplyPoint();	// �⋋�n�_�ɓ����Ă���
	int32_t amountBullets() const;
	PlayerReload& reload()const;
private:
	void CalcuateDamege(Enemy* e);
	void OnCollision()override;
	void OnSound(); //	�T�E���h�̐ݒ�

	std::vector<Enemy*> m_EnemyList;
	std::vector<Supply*> m_SupplyList;

	D3DXVECTOR4 m_Param;
	GameCommand* m_Command;
	GameCamera* m_Camera;
	Pause* m_Pause;
	PlayerUi::DrawSkill* m_DrawSkill;
	PlayerUi::Reload* m_Reload;
	Resource& m_Resource;
	Graphics& m_Graphics;
	std::unique_ptr<PlayerReload> m_PlayerReload = nullptr;

	const int32_t m_AmountBuuletsMax = 24;	// �e���̍ő�l 
	int32_t m_AmountBullets = 24;			// �e��
	float m_ReplenishTime = 0;				// �⋋���̎��Ԍv��
	float m_Volume = 0.0f;					// �T�E���h�̑傫��	
	bool m_Audioplay = false;
	bool m_EnteringSulpplyPoint;			// �⋋�n�_�ɓ����Ă���
	bool m_NowReplenish = false;
};

