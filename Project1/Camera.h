/*------------------------------------------------------------
	
	[Camera.h]
	Author : 出合翔太

--------------------------------------------------------------*/
#pragma once
#include "Actor.h"

// カメラのベース
class Camera : public Actor
{
public:
	Camera();
	virtual ~Camera() {}
	void Begin()override{}
	void Update()override {}
	void Event()override {}
	void Draw()override {}

	// 視錐台カリングするかどうかの判定	


	// 注視点
	void SetTarget(Math::Vector3 Target);
	Math::Vector3& GetTarget();

	const DirectX::XMMATRIX GetView() const;
	const DirectX::XMMATRIX GetProjection() const; // プロジェクションマトリクス
protected:
	// ビューマトリクス設定
	void SetViewMatrix();
	// プロジェクション設定
	void SetProjectionMatrix();

	Math::Vector3 m_Target; // 注視点
private:
	DirectX::XMFLOAT4X4 m_View;
	DirectX::XMFLOAT4X4 m_Projection;
	DirectX::XMFLOAT4 m_Up; // カメラの上ベクトル

	const float m_Aspect; // アスペクト比
	class Graphics& m_Graphics;
};
