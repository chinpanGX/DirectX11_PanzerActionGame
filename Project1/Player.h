/*------------------------------------------------------------

	[Playervehicle.h]
	Author : 出合翔太

-------------------------------------------------------------*/
#pragma once
#include "Pawn.h"

class Player final : public Pawn
{
public:
	Player();
	~Player();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void ChangeState(std::unique_ptr<class PanzerState> State)override;
	void Respawn(const Math::Vector3& pos)override;
private:
	void OnCollision()override;
	void OnSound(); //	サウンドの設定
	class Resource& m_Resource;
	float m_Volume = 0.0f;
	bool m_Audioplay = false;
	bool m_HitWall = false;
};

