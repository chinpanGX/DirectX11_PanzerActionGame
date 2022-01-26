/*-------------------------------------------------------------

	[IVehicle.h]
	Author : �o���đ�


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

	// �����ʒu�����߂�
	void SetStartPosition(D3DXVECTOR3 pos, D3DXVECTOR3 rot); // �K���[�W�Ŏg��
	void SetStartPosition(class Pawn* pawn, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	
	// �_���[�W�v�Z
	void CalcuateDamege(class Pawn* Pawn);
	void PlayerCalcuateDamege(class Pawn* Pawn);

	// ����
	void Shot(const Transform& transform);
	
	//�@�����蔻��֌W
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

	// �X�e�[�^�X�̐ݒ�
	void SetPanzer();
	void SetStatus(Status::Country Country, float Cost, float Hp, float Attack, float Defence, float Speed, float Reload, float RotSpeed);
	// �e���ł�ʒu�̕␳�l�����߂�
	void ShotPointOffsetLength(float length);

	//�@���
	class Panzer& panzer() const;
	const std::string& tag() const;
private:
	// HP�v�Z
	void CalculateHp(float AttackPoint); 
	std::string m_Tag;
	float m_GunLength; // ��C�̒���
	std::unique_ptr<class Shadow> m_Shadow;
	std::unique_ptr<Panzer> m_Panzer;
	std::unique_ptr<Status> m_Status;
	std::unique_ptr<Skill> m_Skill;
};

