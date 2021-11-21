/*---------------------------------------------------------------

	[Skill.h]
	Author : �o���đ�

	�X�L�����Ǘ�����

----------------------------------------------------------------*/
#pragma once
#include <memory>
#include <vector>

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

	// �X�L���Q�[�W�����܂鎞��
	void SetTime(float amount); //�@�i�߂鎞��
	// �X�L�����g��
	void Enable(Pawn* pawn);

	// �G�t�F�N�g�̍Đ�
	void PlayEffect(Pawn* pawn);
	
	// �Q�b�^�[
	const int32_t phase() const;
	const float timeToActivateSkill() const;
	const bool alreadyUseble() const;
private:	
	std::vector<std::unique_ptr<IUseSkill>> m_UseSkill;
	class SkillParticle* m_SkillEffect;

	int32_t m_Phase = 0;	// �t�F�[�Y
	float m_TimeToActivateSkill = 30.0f;	// �X�L����L���ɂ��鎞��
	float m_Amount = 1.0f;	// ���₷��
	float m_NowTime = 0.0f;
	bool m_AlreadyUseble = false; // �X�L�����g�����Ԃ��ǂ���
};