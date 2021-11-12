/*--------------------------------------------------------------

	[Pawn.h]
	Author : �o���đ�

---------------------------------------------------------------*/
#pragma once
#include "Actor.h"
#include "Factory.h"

class Vehicle;
class Pivot;
class MoveComponent;
class IOnComponentEventToPawn;
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
	
	virtual void Respawn(const D3DXVECTOR3& pos) = 0;
	virtual void ChangeState(std::unique_ptr<class PanzerState> State) = 0;
	Vehicle& vehicle() const;
	Pivot& pivot()const;
	MoveComponent& GetMoveComponent()const;

protected:
	virtual void OnCollision() = 0;
	// Hp���[���̓`�F�b�N
	void CheckZeroHp(Pawn* pawn);
	// ���X�|�[������Ƃ���Hp��ݒ肷��
	void RespawnSetMaxHP();
	// �ʒu�̐ݒ�
	void SetStartPosition(Pawn* pawn, const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);
	// ����
	void Create();
	
	// �����蔻���̃C�x���g��ǉ�
	template<typename T>
	void AddComponentEvent()
	{
		m_ComponentEvent.emplace_back(std::make_unique<T>());
	}

	void BeginOverlap(Pawn* pPawn);
private:
	std::vector<std::unique_ptr<IOnComponentEventToPawn>> m_ComponentEvent;
	std::unique_ptr<Vehicle> m_Vehicle = nullptr;
	std::unique_ptr<MoveComponent> m_MoveComponent = nullptr;
	std::unique_ptr<Pivot> m_Pivot = nullptr;
	int32_t m_Type;
};

