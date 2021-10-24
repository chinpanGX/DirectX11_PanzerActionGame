/*-----------------------------------------------------------
	
	[NormalBullet.h]
	Author : o‡ãÄ‘¾

	’Êí’e‚Ìˆ—

------------------------------------------------------------*/
#pragma once
#include "Bullet.h"

class NormalBullet final : public Bullet
{
public:
	NormalBullet();
	~NormalBullet();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void Create(const Math::Vector3& Position, const Math::Vector3& Vector)override;
	void ChangeState(std::unique_ptr<BulletState> State)override;
	void OnCollision()override;
private:
	std::unique_ptr<BulletState> m_State;
	class Resource& m_Resource;
};