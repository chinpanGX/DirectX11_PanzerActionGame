/*--------------------------------------------------------------
	
	[DefaultObject.h]
	Author : �o���đ�

	���ׂẴI�u�W�F�N�g�̐e�N���X

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

	// �C���X�^���X
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
	
	// �����蔻��
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
	bool m_OnDestroy;	// true�ŃC���X�^���X���폜
	bool m_OnCollision;	// true�œ����蔻������m
};

