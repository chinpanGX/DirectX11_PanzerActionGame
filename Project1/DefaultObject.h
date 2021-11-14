/*--------------------------------------------------------------
	
	[DefaultObject.h]
	Author : 出合翔太

	すべてのオブジェクトの親クラス

---------------------------------------------------------------*/
#pragma once

class DefaultObject
{
public:
	DefaultObject() : m_OnDestroy(false), m_OnCollision(false) {}
	virtual ~DefaultObject(){}
	virtual void Begin() = 0;
	virtual void Update() = 0;
	virtual void Event() = 0;
	virtual void Draw() = 0;

	// インスタンス
	inline void OnDestroy()
	{
		m_OnDestroy = true;
	}

	inline const bool Destroy() const
	{
		if (m_OnDestroy == true)
		{
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}
	
	// 当たり判定
	inline void OnCollisionEnter()
	{
		m_OnCollision = true;
	}

	inline void ResetCollisionEnter()
	{
		m_OnCollision = false;
	}

	const bool CollisionEnter() const
	{
		if (m_OnCollision == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	bool m_OnDestroy;	// trueでインスタンスを削除
	bool m_OnCollision;	// trueで当たり判定を検知
};

