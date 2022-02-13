/*--------------------------------------------------------------

	[Pawn.h]
	Author : �o���đ�

---------------------------------------------------------------*/
#pragma once
#include "Actor.h"
#include "Factory.h"

class Reload;
class Vehicle;
class Pivot;
class MoveComponent;
class Pawn : public Actor
{
public:
	Pawn();
	Pawn(int32_t Type);
	~Pawn();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	
	virtual void ResPawn(const D3DXVECTOR3& pos) = 0;
	Vehicle& GetVehicle() const;
	Pivot& GetPivot()const;
	MoveComponent& GetMoveComponent()const;

protected:
	virtual void OnCollision() = 0;
	// Hp���[���̓`�F�b�N
	void CheckZeroHp(Pawn* Pawn);
	// �ʒu�̐ݒ�
	void SetStartPosition(Pawn* Pawn, const D3DXVECTOR3& Pos, const D3DXVECTOR3& Rot);
	// ����
	void Create();
	
	void BeginOverlap(Pawn* Pawn);
private:
	std::unique_ptr<Vehicle> m_Vehicle = nullptr;
	std::unique_ptr<MoveComponent> m_MoveComponent = nullptr;
	std::unique_ptr<Pivot> m_Pivot = nullptr;
	int32_t m_Type;
};

