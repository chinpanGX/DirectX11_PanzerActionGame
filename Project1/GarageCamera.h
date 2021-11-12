/*-----------------------------------------------------------

	[GarageCamera.h]
	Author : �o���đ�

	��ԑq�ɂ̃J����

------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include "myLib.h"


class GarageCamera final : public DefaultObject
{
public:
	GarageCamera();
	~GarageCamera();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:
	// �s��
	DirectX::XMFLOAT4X4 m_View;
	DirectX::XMFLOAT4X4 m_Projection;

	// �J�����̐ݒ�
	Math::Vector3 m_Position;
	Math::Vector3 m_Target;

	class Graphics& m_Graphics;
};

