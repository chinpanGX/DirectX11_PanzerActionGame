/*------------------------------------------------------------

	[GameCamera.h]
	Author : 出合翔太

	ゲーム用カメラ

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

	// 視錐台でView内にTargetObjectがあるか調べる
	// 描画できるかをbool変数で返す
	bool NotDrawObject(const D3DXVECTOR3& TargetPosition, float Radius);

	// Getter
	const D3DXMATRIX& view() const;
	const D3DXVECTOR3& position() const;

	// FPSモードの設定
	const bool FpsModeNow() const;
	void EnableFpsMode(bool Enable);
private:
	// ヘルパー関数
	void SetViewMatrix();		// ビューマトリクスの設定
	void SetProjectionMatrix();	// プロジェクションマトリクスの設定

	// 行列
	D3DXMATRIX m_View;
	D3DXMATRIX m_Projection;

	// カメラの設定
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Target;
	
	class Graphics& m_Graphics;
	bool m_EnableFpsMode; // カメラのモードを切り替える trueのときFPSカメラにする
};
