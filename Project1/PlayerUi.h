/*-----------------------------------------------------------

	[PlayerUi.h]
	Author : 出合翔太
	プレイヤー側に表示するUI

------------------------------------------------------------*/
#pragma once
#include "Actor.h"
#include "Effect.h"

class Render;
// スキルのゲージ
class DrawSkill final : public Actor
{
public:
	DrawSkill();
	~DrawSkill();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void Reset();
private:
	std::unique_ptr<Render> m_Render;
	class Player* m_Player;
	const float m_MaxDrawSize = 400.0f;
	float m_DrawSize = 0.0f;
	float m_Add; // 増加する量
};

class Reload final : public Effect
{
public:
	Reload();
	~Reload();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};
