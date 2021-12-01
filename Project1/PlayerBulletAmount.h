/*-------------------------------------------------------------

	[PlayerBulletAmount.h]
	Author : 出合翔太
	
	プレイヤーの弾数を描画する

--------------------------------------------------------------*/
#pragma once
#include "DrawNumber.h"
#include "Actor.h"

// プレイヤーの撃てる弾数を表示
class PlayerBulletAmount final : public DrawNumber
{
public:
	PlayerBulletAmount();
	~PlayerBulletAmount();
	void Draw(int value)override;
};

// プレイヤーの撃てる弾数の最大数を表示
class PlayerBulletAmountMax final : public DrawNumber
{
public:
	PlayerBulletAmountMax();
	~PlayerBulletAmountMax();
	void Draw(int value)override;
};

// 区切りのスラッシュ
class DrawSlash final 
{
public:
	DrawSlash();
	~DrawSlash();
	void Draw();
};

class Player;
namespace PlayerUi
{
	class BulletAmount final : public Actor
	{
	public:
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
	private:
		std::vector<std::unique_ptr<DrawNumber>> m_DrawBulletAmount;
		Player* m_Player;
		int32_t m_BulletsValue;
	};
}