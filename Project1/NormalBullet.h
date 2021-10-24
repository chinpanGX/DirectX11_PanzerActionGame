/*-----------------------------------------------------------
	
	[NormalBullet.h]
	Author : èoçá„ƒëæ

	í èÌíeÇÃèàóù

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
	void OnCollisionToPawn(class Pawn * Pawn);
	std::unique_ptr<BulletState> m_State;
	class Resource& m_Resource;
};