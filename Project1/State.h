/*-----------------------------------------------------------
	
	[State.h]
	Author : 出合翔太

	各ステートの基底クラス

------------------------------------------------------------*/
#pragma once
#include "stdafx.h"

// 各ステートの基底クラス
class StateBase
{
public:
	StateBase() : m_Frame(30) {}
	inline StateBase(const int32_t& Frame) : m_Frame(Frame), m_FrameZeroFlag(false){}
	~StateBase() = default;
protected:
	inline void OnFrameZero()
	{
		m_FrameZeroFlag = true;
	}
	// フレーム数のカウントダウン
	inline void FrameCountDown()
	{
		// フレーム数をデクリメントしてフレーム数が０になったらフラグをtrueにして通知する
		m_Frame--;
		if (m_Frame <= 0)
		{
			OnFrameZero();
		}
	}

	// Getter
	inline const int32_t& GetFrame()const { return m_Frame; }
	inline const bool& GetFrameZeroFlag() const { return m_FrameZeroFlag; }
private:
	int32_t m_Frame;
	bool m_FrameZeroFlag; // フレーム数が０になったらtrue
};

// 弾のステート
class BulletState : public StateBase
{
public:
	inline BulletState() : StateBase(256) {}
	inline virtual ~BulletState() {}
	virtual void Update(class Bullet* Bullet, float DeltaTime) = 0;
};

