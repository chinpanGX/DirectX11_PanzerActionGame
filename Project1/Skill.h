/*---------------------------------------------------------------

	[Skill.h]
	Author : �o���đ�

	�X�L�����Ǘ�����

----------------------------------------------------------------*/
#pragma once
#include <memory>
#include <vector>

class SkillParticle;
class Pawn;
class Status;
class IUseSkill;
class Skill
{
public:
	Skill();
	~Skill();
	// �X�L����ݒ肷��(�ݒ肷��X�L��)
	void SetSkill(std::unique_ptr<IUseSkill> useSkill);
	// �X�L������(��������܂ł̎���)
	void Begin(float timeToActivateSkill); 
	void Update(Status& status, const D3DXVECTOR3& position);

	// �G�t�F�N�g�̍Đ�
	void PlayEffect(Pawn* pawn);

	// �X�L���Q�[�W�����܂鎞��
	void SetTime(float amount); //�@�i�߂鎞��
	// �X�L�����g��
	void Enable(Pawn* pawn);
	// ���Z�b�g
	void Reset(Status& status);	  

	// �Q�b�^�[
	const D3DXVECTOR4& uv() const;
	const int32_t phase() const;
	const float timeToActivateSkill() const;
	const float timeLimit() const;
	// �X�L�����g�����Ԃ��ǂ���
	const bool alreadyUseble() const;
	
	// �X�L�����g���Ă��邩�ǂ���
	const bool useSkillNow() const;
private:	
	void Charge();				// �X�L�������߂�
	void Use(Status& status);	// �X�L�����g��
	void PlayAnim();			// �g�D�[���A�j���[�V�����p�̐ݒ�

	std::vector<std::unique_ptr<IUseSkill>> m_UseSkill;
	D3DXVECTOR4 m_UvParam;

	SkillParticle* m_Effect = nullptr;

	int32_t m_Phase = 0;					// �t�F�[�Y
	float m_TimeToActivateSkill = 30.0f;	// �X�L����L���ɂ��鎞��
	float m_TimeLimit = 5.0f;				// �X�L�����g���鎞��
	float m_Amount = 1.0f;					// ���₷��
	float m_NowTime = 0.0f;
	bool m_AlreadyUseble = false;			// �X�L�����g�����Ԃ��ǂ���
	bool m_NowUse = false;					// �X�L�����g�p������
};