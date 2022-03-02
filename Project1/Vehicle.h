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

class Collider;
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
	void SetStartPosition(const D3DXVECTOR3& Pos, const D3DXVECTOR3& Rot); // ガレージで使う
	void SetStartPosition(class Pawn* Pawn, const D3DXVECTOR3& Pos, const D3DXVECTOR3& Rot);
	
	// 撃つ
	void Shot(const Transform& transform);
	
	//　当たり判定関係
	// 更新
	void ColiisionUpdate(int32_t Element, const D3DXVECTOR3& Position, Transform& Transform);
	// コライダーの取得
	Collider& GetCollider(int32_t Element) const;
	// コライダーの配列のサイズ
	const uint32_t GetColliderNum() const;

	// 戦車のパーツのトランスフォームを取得
	class Transform& GetBodyTransform() const;
	class Transform& GetTurretTransform() const;
	class Transform& GetGunTransform() const;


	Status& GetStatus() const;
	Skill& GetSkill() const;
protected:
	std::array<std::unique_ptr<Collider>, 2> m_Collider;

	// ステータスの設定
	void SetPanzer();
	void SetStatus(Status::Country Country, float Cost, float Hp, float Attack, float Defence, float Speed, float Reload, float RotSpeed);
	// 弾がでる位置の補正値を決める
	void ShotPointOffsetLength(float Length);

	//　戦車
	class Panzer& GetPanzer() const;
	const std::string& GetTag() const;
private:
	std::string m_Tag;
	float m_GunLength; // 主砲の長さ
	std::unique_ptr<class Shadow> m_Shadow;
	std::unique_ptr<Panzer> m_Panzer;
	std::unique_ptr<Status> m_Status;
	std::unique_ptr<Skill> m_Skill;
};

