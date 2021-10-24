/*------------------------------------------------------------
	
	[Skydome.h]
	Author : 出合翔太
	
	スカイドーム

-------------------------------------------------------------*/
#pragma once
#include "StageObject.h"

class Skydome final : public StageObject
{
public:
	Skydome();
	~Skydome();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:
	// Updateで呼ぶとカメラの情報が古くなるため、必ずDraw()で呼び出す
	// マトリクス計算
	void UpdateMatrix(); 

	float m_RotationSpeed; // スカイドームの回転速度
	class Graphics& m_Graphics;
};

