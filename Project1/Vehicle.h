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
	void SetStartPosition(Math::Vector3 pos, Math::Vector3 rot); // ガレージで使う
	void SetStartPosition(class Pawn* pawn, Math::Vector3 pos, Math::Vector3 rot);
	
	// ダメージ計算
	void CalcuateDamege(class Pawn* Pawn);

	// 撃つ
	void Shot(const Transform& transform);
	
	//　当たり判定関係
	void ColiisionUpdate(int32_t Element, const Math::Vector3& Position, const Transform& t);
	BoxComponent& GetBoxComponent(int32_t Element) const;
	
	class Transform& GetBodyTransform() const;
	class Transform& GetTurretTransform() const;
	class Transform& GetGunTransform() const;
	Status& GetStatus() const;
	Skill& GetSkill() const;
protected:
	std::array<std::unique_ptr<class BoxComponent>, 3> m_BoxComponent;

	// プロパティの設定
	void SetPanzer();
	void SetProperty(Status::Country Country, float Cost, float Hp, float Attack, float Defence, float Speed, float Reload, float RotSpeed);
	//　戦車
	class Panzer& GetPanzer() const;
	const std::string& GetTag() const;
private:
	// HP計算
	void CalculateHp(float AttackPoint); 
	std::string m_Tag;
	std::unique_ptr<class Shadow> m_Shadow;
	std::unique_ptr<Panzer> m_Panzer;
	std::unique_ptr<Status> m_Status;
	std::unique_ptr<Skill> m_Skill;
};

