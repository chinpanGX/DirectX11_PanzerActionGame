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
	D3DXMATRIX m_View;
	D3DXMATRIX m_Projection;

	// カメラの設定
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Target;

	class Graphics& m_Graphics;
};

