/*-----------------------------------------------------------
	
	[CameraMode.h]
	Author : 出合翔太

	FPSカメラ、TPSカメラの状態を切り替える

-------------------------------------------------------------*/
#pragma once
#include "myLib.h"

class GameCamera;
class PanzerPilot;
class CameraMode
{
public:
	virtual void Update(GameCamera* Camera, PanzerPilot* Panzer) = 0;
};

// TPS視点モード
class TpsCameraMode final : public CameraMode
{
public:
	TpsCameraMode();
	~TpsCameraMode();
	void Update(GameCamera* Camera, PanzerPilot* Panzer)override;
private:
	// 補正をかける値
	const Math::Vector3	m_PositionOffset = Math::Vector3(0.0f, 10.0f, 0.0f);
	const float m_OffsetBackwardVector = 20.0f;
	const float m_OffsetForwardVector = 50.0f;
};

// FPS視点モード
class FpsCameraMode final : public CameraMode
{
public:
	FpsCameraMode();
	~FpsCameraMode();
	void Update(GameCamera* Camera, PanzerPilot* Panzer)override;
};
