/*------------------------------------------------------------
	
	[Camera.h]
	Author : �o���đ�

--------------------------------------------------------------*/
#pragma once
#include "Actor.h"

// �J�����̃x�[�X
class Camera : public Actor
{
public:
	Camera();
	virtual ~Camera() {}
	void Begin()override{}
	void Update()override {}
	void Event()override {}
	void Draw()override {}

	// ������J�����O���邩�ǂ����̔���	


	// �����_
	void SetTarget(Math::Vector3 Target);
	Math::Vector3& GetTarget();

	const DirectX::XMMATRIX GetView() const;
	const DirectX::XMMATRIX GetProjection() const; // �v���W�F�N�V�����}�g���N�X
protected:
	// �r���[�}�g���N�X�ݒ�
	void SetViewMatrix();
	// �v���W�F�N�V�����ݒ�
	void SetProjectionMatrix();

	Math::Vector3 m_Target; // �����_
private:
	DirectX::XMFLOAT4X4 m_View;
	DirectX::XMFLOAT4X4 m_Projection;
	DirectX::XMFLOAT4 m_Up; // �J�����̏�x�N�g��

	const float m_Aspect; // �A�X�y�N�g��
	class Graphics& m_Graphics;
};
