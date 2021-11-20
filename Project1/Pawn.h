/*--------------------------------------------------------------

	[Pawn.h]
	Author : 出合翔太

---------------------------------------------------------------*/
#pragma once
#include "Actor.h"
#include "Factory.h"

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
	
	virtual void Respawn(const D3DXVECTOR3& pos) = 0;
	Vehicle& vehicle() const;
	Pivot& pivot()const;
	MoveComponent& moveComponent()const;

protected:
	virtual void OnCollision() = 0;
	// Hpがゼロはチェック
	void CheckZeroHp(Pawn* pawn);
	// リスポーンするときにHpを設定する
	void RespawnSetMaxHP();
	// 位置の設定
	void SetStartPosition(Pawn* pawn, const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);
	// 生成
	void Create();
	
	void BeginOverlap(Pawn* pPawn);
private:
	std::unique_ptr<Vehicle> m_Vehicle = nullptr;
	std::unique_ptr<MoveComponent> m_MoveComponent = nullptr;
	std::unique_ptr<Pivot> m_Pivot = nullptr;
	int32_t m_Type;
};

