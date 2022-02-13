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
	void Draw(int Value)override;
};

// プレイヤーの撃てる弾数の最大数を表示
class PlayerBulletAmountMax final : public DrawNumber
{
public:
	PlayerBulletAmountMax();
	~PlayerBulletAmountMax();
	void Draw(int Value)override;
};

// 区切りのスラッシュ
class DrawSlash final 
{
public:
	DrawSlash();
	~DrawSlash();
	void Draw();
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	class Graphics& m_Graphics;
	class Resource& m_Resource;
};

class Player;
namespace PlayerUi
{
	class BulletAmount final : public Actor
	{
	public:
		BulletAmount();
		~BulletAmount();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
	private:
		std::vector<std::unique_ptr<DrawNumber>> m_DrawBulletAmount;
		std::unique_ptr<DrawSlash> m_Slash;
		Player* m_Player;
		int32_t m_BulletsValue;
		int32_t m_BulletValueMax;
	};
}