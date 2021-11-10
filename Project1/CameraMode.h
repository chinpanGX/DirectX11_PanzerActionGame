/*-----------------------------------------------------------
	
	[CameraMode.h]
	Author : �o���đ�

	FPS�J�����ATPS�J�����̏�Ԃ�؂�ւ���

-------------------------------------------------------------*/
#pragma once
#include "myLib.h"

class GameCamera;
class Pivot;
class CameraMode
{
public:
	virtual void Update(GameCamera* Camera, Pivot* Panzer) = 0;
};

// TPS���_���[�h
class TpsCameraMode final : public CameraMode
{
public:
	TpsCameraMode();
	~TpsCameraMode();
	void Update(GameCamera* Camera, Pivot* Panzer)override;
private:
	// �␳��������l
	const Math::Vector3	m_PositionOffset = Math::Vector3(0.0f, 10.0f, 0.0f);
	const float m_OffsetBackwardVector = 20.0f;
	const float m_OffsetForwardVector = 50.0f;
};

// FPS���_���[�h
class FpsCameraMode final : public CameraMode
{
public:
	FpsCameraMode();
	~FpsCameraMode();
	void Update(GameCamera* Camera, Pivot* Panzer)override;
};
