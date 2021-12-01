/*-------------------------------------------------------------

	[PlayerBulletAmount.h]
	Author : �o���đ�
	
	�v���C���[�̒e����`�悷��

--------------------------------------------------------------*/
#pragma once
#include "DrawNumber.h"
#include "Actor.h"

// �v���C���[�̌��Ă�e����\��
class PlayerBulletAmount final : public DrawNumber
{
public:
	PlayerBulletAmount();
	~PlayerBulletAmount();
	void Draw(int value)override;
};

// �v���C���[�̌��Ă�e���̍ő吔��\��
class PlayerBulletAmountMax final : public DrawNumber
{
public:
	PlayerBulletAmountMax();
	~PlayerBulletAmountMax();
	void Draw(int value)override;
};

// ��؂�̃X���b�V��
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