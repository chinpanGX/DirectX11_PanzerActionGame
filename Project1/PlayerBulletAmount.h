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
	void Draw(int Value)override;
};

// �v���C���[�̌��Ă�e���̍ő吔��\��
class PlayerBulletAmountMax final : public DrawNumber
{
public:
	PlayerBulletAmountMax();
	~PlayerBulletAmountMax();
	void Draw(int Value)override;
};

// ��؂�̃X���b�V��
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