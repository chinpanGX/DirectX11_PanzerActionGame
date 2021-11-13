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
	D3DXMATRIX m_View;
	D3DXMATRIX m_Projection;

	// �J�����̐ݒ�
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Target;

	class Graphics& m_Graphics;
};

