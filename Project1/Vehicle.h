/*-------------------------------------------------------------

	[IVehicle.h]
	Author : 出合翔太


--------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include "Math.h"
#include "Panzer.h"
#include <memory>
#include <array>

class Skill;
class Vehicle : public DefaultObject
{
public:
	Vehicle() = delete;
	Vehicle(std::string Tag);
	virtual ~Vehicle();
	void Begin()override;
	void Update()override;
	void Draw()override;
	void Event()override {}

	// 初期位置を決める
	void SetStartPosition(D3DXVECTOR3 pos, D3DXVECTOR3 rot); // ガレージで使う
	void SetStartPosition(class Pawn* pawn, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	
	// ダメージ計算
	void CalcuateDamege(class Pawn* Pawn);
	void PlayerCalcuateDamege(class Pawn* Pawn);

	// 撃つ
	void Shot(const Transform& transform);
	
	//　当たり判定関係
	void ColiisionUpdate(int32_t Element, const D3DXVECTOR3& Position, Transform& t);
	Collider& collider(int32_t Element) const;
	const uint32_t colliderNum() const;

	class Transform& bodyTransform() const;
	class Transform& turretTransform() const;
	class Transform& gunTransform() const;
	Status& status() const;
	Skill& skill() const;
protected:
	std::array<std::unique_ptr<class Collider>, 2> m_Collider;

	// ステータスの設定
	void SetPanzer();
	void SetStatus(Status::Country Country, float Cost, float Hp, float Attack, float Defence, float Speed, float Reload, float RotSpeed);
	// 弾がでる位置の補正値を決める
	void ShotPointOffsetLength(float length);

	//　戦車
	class Panzer& panzer() const;
	const std::string& tag() const;
private:
	// HP計算
	void CalculateHp(float AttackPoint); 
	std::string m_Tag;
	float m_GunLength; // 主砲の長さ
	std::unique_ptr<class Shadow> m_Shadow;
	std::unique_ptr<Panzer> m_Panzer;
	std::unique_ptr<Status> m_Status;
	std::unique_ptr<Skill> m_Skill;
};

