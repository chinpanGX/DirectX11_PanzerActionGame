/*------------------------------------------------------------

	[Playervehicle.h]
	Author : 出合翔太

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

	void ReplenishBullets();	// 弾を補給する 
	bool isBulletsUpperLimit(); // 弾の数が上限かどうか
	bool enterSupplyPoint();	// 補給地点に入っている
	int32_t amountBullets() const;
	PlayerReload& reload()const;
private:
	void CalcuateDamege(Enemy* e);
	void OnCollision()override;
	void OnSound(); //	サウンドの設定

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

	const int32_t m_AmountBuuletsMax = 24;	// 弾数の最大値 
	int32_t m_AmountBullets = 24;			// 弾数
	float m_ReplenishTime = 0;				// 補給中の時間計測
	float m_Volume = 0.0f;					// サウンドの大きさ	
	bool m_Audioplay = false;
	bool m_EnteringSulpplyPoint;			// 補給地点に入っている
	bool m_NowReplenish = false;
};

