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

	// �����ʒu�����߂�
	void SetStartPosition(const D3DXVECTOR3& Pos, const D3DXVECTOR3& Rot); // �K���[�W�Ŏg��
	void SetStartPosition(class Pawn* Pawn, const D3DXVECTOR3& Pos, const D3DXVECTOR3& Rot);
	
	// ����
	void Shot(const Transform& transform);
	
	//�@�����蔻��֌W
	// �X�V
	void ColiisionUpdate(int32_t Element, const D3DXVECTOR3& Position, Transform& Transform);
	// �R���C�_�[�̎擾
	Collider& GetCollider(int32_t Element) const;
	// �R���C�_�[�̔z��̃T�C�Y
	const uint32_t GetColliderNum() const;

	// ��Ԃ̃p�[�c�̃g�����X�t�H�[�����擾
	class Transform& GetBodyTransform() const;
	class Transform& GetTurretTransform() const;
	class Transform& GetGunTransform() const;


	Status& GetStatus() const;
	Skill& GetSkill() const;
protected:
	std::array<std::unique_ptr<Collider>, 2> m_Collider;

	// �X�e�[�^�X�̐ݒ�
	void SetPanzer();
	void SetStatus(Status::Country Country, float Cost, float Hp, float Attack, float Defence, float Speed, float Reload, float RotSpeed);
	// �e���ł�ʒu�̕␳�l�����߂�
	void ShotPointOffsetLength(float Length);

	//�@���
	class Panzer& GetPanzer() const;
	const std::string& GetTag() const;
private:
	std::string m_Tag;
	float m_GunLength; // ��C�̒���
	std::unique_ptr<class Shadow> m_Shadow;
	std::unique_ptr<Panzer> m_Panzer;
	std::unique_ptr<Status> m_Status;
	std::unique_ptr<Skill> m_Skill;
};

