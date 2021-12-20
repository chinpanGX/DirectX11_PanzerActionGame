/*-----------------------------------------------------------
	
	[Bullet.h]
	Author : 出合翔太

	弾の処理

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

	// 弾の生成
	void Create(const D3DXVECTOR3& Position, const D3DXVECTOR3& Vector);
	void ChangeState(std::unique_ptr<BulletState> State);
	void OnCollision();

	// D3DXVECTOR3の方向ベクトル
	const D3DXVECTOR3& GetDirectionVector() const;
	// 威力減衰
	void DownDDE();

	const float distdecay() const;
	const float speed() const;
private:
	void OnCollisionToPawn(class Pawn * Pawn);
	std::unique_ptr<BulletState> m_State;
	class Resource& m_Resource;
	D3DXVECTOR3 m_DirectionVector;	// 飛んでいく方向
	uint32_t m_Frame;			// フレーム数
	float m_Speed;				// 速度
	float m_Distdecay = 1.2f;	// 距離による威力減衰
	bool m_FrameZeroFlag;		// フレーム数が０になったらtrueにして通知する
};

