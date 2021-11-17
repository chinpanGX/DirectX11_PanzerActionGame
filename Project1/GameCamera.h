/*------------------------------------------------------------

	[GameCamera.h]
	Author : �o���đ�

	�Q�[���p�J����

--------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include "myLib.h"

class GameCamera final : public DefaultObject 
{
public:
	GameCamera();
	~GameCamera();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;

	// �������View����TargetObject�����邩���ׂ�
	// �`��ł��邩��bool�ϐ��ŕԂ�
	bool NotDrawObject(const D3DXVECTOR3& TargetPosition, float Radius);

	// Getter
	const D3DXMATRIX& view() const;
	const D3DXVECTOR3& position() const;

	// FPS���[�h�̐ݒ�
	const bool FpsModeNow() const;
	void EnableFpsMode(bool Enable);
private:
	// �w���p�[�֐�
	void SetViewMatrix();		// �r���[�}�g���N�X�̐ݒ�
	void SetProjectionMatrix();	// �v���W�F�N�V�����}�g���N�X�̐ݒ�

	// �s��
	D3DXMATRIX m_View;
	D3DXMATRIX m_Projection;

	// �J�����̐ݒ�
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Target;
	
	class Graphics& m_Graphics;
	bool m_EnableFpsMode; // �J�����̃��[�h��؂�ւ��� true�̂Ƃ�FPS�J�����ɂ���
};
