/*--------------------------------------------------------------

	[TitleSystem.h]
	Author : �o���đ�

	�^�C�g����ʂł�鑀����Ǘ�

---------------------------------------------------------------*/
#pragma once
#include "stdafx.h"
#include "DefaultObject.h"

class TitleSystem final : public DefaultObject 
{
public:
	TitleSystem();
	~TitleSystem();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void SetState(uint32_t State);
	const uint32_t GetState() const;

	// �C���v�b�g�̃`�F�b�N
	bool GetCheckInput();
	void EnableCheckInput();
	void DisableCheckInput();

	// �Q�[���p�b�h�͎g����
	void EnableGamePad();
	void DisableGamePad();
	const bool GetInputGamePad() const;

	// �ǂ�����I��ł��邩
	// Setter
	void SelectTop();
	void SelectButtom();
	// Getter
	const bool GetSelect()const;

	// ��ʃX�e�[�g
	enum EState : uint32_t
	{
		BEGIN, // �ŏ�
		SELECT,
		//SETTING_SELECT, // �L�[�}�E���p�b�h��I��
		CHECK_INPUT
	};
private:
	// �J���[�`�F���W
	void UpdateColorChenge();

	void DrawSelect();
	//void DrawSetting();
	//void DrawInput();

	std::unique_ptr<class Renderer2D> m_Render;
	D3DXVECTOR4 m_Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	float m_Alpha = 1.0f;
	uint32_t m_State;
	// �R���g���[�����g�����ǂ���
	bool m_InputCheck = false;
	bool m_InputGamePad = false;
	bool m_ToporButtom = true; // true = ��Afalse = ��
	float m_Changecolor;
};
