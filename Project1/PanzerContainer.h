/*--------------------------------------------------------------

	[PanzerContatiner.h]
	Author : �o���đ�

	��Ԃ̃f�[�^�������Ă���

---------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include "GameBg.h"
#include <string>
#include <unordered_map>
#include <vector>

class Vehicle;
class PanzerContainer : public DefaultObject
{
public:
	PanzerContainer();
	~PanzerContainer();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	
	void SetChooseUp();		// ��ɃX�N���[��
	void SetChooseDown();	// ���ɃX�N���[��

	// CPU��Ԃ����߂�
	void DecisionofCpuPanzer();

	// �I��
	const int32_t GetChose() const;
	void Reset();
	const int32_t GetButton() const;

	// �v���C���[
	const std::string& StringFindPlayerTag() const;
	// CPU�̃^�O
	const std::string& StringFindCpuTag()const;
private:
	static std::string m_PlayerofSelectedPanzer; // �v���C���[�̑I��������Ԃ��i�[
	static std::string m_CpuofSelectedPanzer; // Cpu���I�񂾐��
	std::unordered_map<std::string, std::unique_ptr<Vehicle>> m_Map;
	std::vector<std::string> m_PanzerName;
	std::vector<float> m_TexCoord;
	std::unique_ptr<class Parameters> m_Parameters; // �p�����[�^�\��
	std::unique_ptr<class DrawNumber> m_Number; // �R�X�g�\��
	std::unique_ptr<Renderer2D> m_SkillList;

	int32_t m_InputButton; // 1�ŏ��I���A2�ŉ���I��

	// �\������p�����[�^
	float m_Cost;
	float m_Hp;
	float m_Attack;
	float m_Defence;
	float m_Speed;
	float m_Reload;

	int32_t m_Choose; // �ǂ��I��ł���̂�
};