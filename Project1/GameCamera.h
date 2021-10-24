/*------------------------------------------------------------

	[GameCamera.h]
	Author : 出合翔太

	ゲーム用カメラ

--------------------------------------------------------------*/
#pragma once
#include "Camera.h"

// ゲームカメラ
class CameraMode;
class GameCamera final : public Camera
{
public:
	GameCamera();
	~GameCamera();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;

	// カメラモードの変更
	void ChangeMode(std::unique_ptr<CameraMode> Mode);

	// Getter/Setter
	const DirectX::XMMATRIX GetInverseView() const;  // 逆行列

	void ChangeCameraMode(bool Change);
	const bool GetChageMode() const;
private:
	std::unique_ptr<CameraMode> m_Mode;	// カメラモード
	bool m_IsChangeMode; // カメラのモードを切り替える trueのときFPSカメラにする
};
