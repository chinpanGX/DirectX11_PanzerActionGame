/*-----------------------------------------------------------
	
	[Bullet.h]
	Author : 出合翔太

-------------------------------------------------------------*/
#pragma once
#include "Actor.h"

class Bullet : public Actor
{
public:
	inline Bullet() : m_FrameZeroFlag(false) 
	{

	}
	inline ~Bullet() 
	{
		m_FrameZeroFlag = false;
	}
	inline void Begin()override {}
	inline void Update()override {}
	inline void Event()override {}
	inline void Draw()override {}

	// 弾の生成
	virtual void Create(const D3DXVECTOR3& Position, const D3DXVECTOR3& Vector) = 0;
	virtual void ChangeState(std::unique_ptr<class BulletState> State) = 0;
	virtual void OnCollision() = 0;

	// フレームカウントダウン
	inline void FrameCountDown()
	{
		m_Frame--;
		if (m_Frame <= 0) // ０になったら通知する
		{
			m_FrameZeroFlag = true;
		}
	}
	
	// D3DXVECTOR3の方法ベクトル
	inline const D3DXVECTOR3& GetDirectionVector() const
	{
		return m_DirectionVector;
	}

	// 威力減衰
	inline void DownDDE()
	{
		m_Distdecay -= 0.02f; // 減衰量
		if (m_Distdecay < 0.7f)
		{
			m_Distdecay = 0.7f;
		}
	}

	inline float GetDDE()
	{
		return m_Distdecay;
	}

	// 速度
	inline const float GetSpeed() const
	{
		return m_Speed;
	}

	inline const bool& GetFrameZeroFlag() const
	{
		return m_FrameZeroFlag;
	}
protected:
	// プロパティの設定 (Vector = 飛んでいく方向ベクトル, Frame = フレーム数)
	inline void SetProperty(const D3DXVECTOR3& Vector, const float& Speed = 10.0f, const uint32_t& Frame = 60)
	{
		m_DirectionVector = Vector;
		m_Speed = Speed;
		m_Frame = Frame;
	}
private:
	D3DXVECTOR3 m_DirectionVector;	// 飛んでいく方向
	uint32_t m_Frame;			// フレーム数
	float m_Speed;				// 速度
	float m_Distdecay = 1.2f;	// 距離による威力減衰
	bool m_FrameZeroFlag;		// フレーム数が０になったらtrueにして通知する
};

