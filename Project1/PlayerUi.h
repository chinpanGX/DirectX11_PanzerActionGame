/*-----------------------------------------------------------

	[PlayerUi.h]
	Author : oãÄ¾
	vC[¤É\¦·éUI

------------------------------------------------------------*/
#pragma once
#include "Actor.h"
#include "Effect.h"

class Render;
// XLÌQ[W
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
	float m_Add; // Á·éÊ
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
