/*-----------------------------------------------------------

	[GarageCamera.h]
	Author : 出合翔太

	戦車倉庫のカメラ

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
	// 行列
	DirectX::XMFLOAT4X4 m_View;
	DirectX::XMFLOAT4X4 m_Projection;

	// カメラの設定
	Math::Vector3 m_Position;
	Math::Vector3 m_Target;

	class Graphics& m_Graphics;
};

