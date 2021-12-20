/*-----------------------------------------------------------
	
	[Bullet.h]
	Author : �o���đ�

	�e�̏���

-------------------------------------------------------------*/
#pragma once
#include "Actor.h"

class BulletState;
class Bullet : public Actor
{
public:
	Bullet();
	~Bullet();
	inline void Begin()override;
	inline void Update()override;
	inline void Event()override;
	inline void Draw()override;

	// �e�̐���
	void Create(const D3DXVECTOR3& Position, const D3DXVECTOR3& Vector);
	void ChangeState(std::unique_ptr<BulletState> State);
	void OnCollision();

	// D3DXVECTOR3�̕����x�N�g��
	const D3DXVECTOR3& GetDirectionVector() const;
	// �З͌���
	void DownDDE();

	const float distdecay() const;
	const float speed() const;
private:
	void OnCollisionToPawn(class Pawn * Pawn);
	std::unique_ptr<BulletState> m_State;
	class Resource& m_Resource;
	D3DXVECTOR3 m_DirectionVector;	// ���ł�������
	uint32_t m_Frame;			// �t���[����
	float m_Speed;				// ���x
	float m_Distdecay = 1.2f;	// �����ɂ��З͌���
	bool m_FrameZeroFlag;		// �t���[�������O�ɂȂ�����true�ɂ��Ēʒm����
};

