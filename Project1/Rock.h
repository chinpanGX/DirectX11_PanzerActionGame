/*------------------------------------------------------------
	
	[Rock.h]
	Author : èoçá„ƒëæ

--------------------------------------------------------------*/
#pragma once
#include "StageObject.h"

class Player;
class Rock final : public StageObject
{
public:
	Rock();
	~Rock();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void Create(const std::string& modelName, D3DXVECTOR3 pos, D3DXVECTOR3 size, float degAngle, bool onCollider);
private:
	std::string m_DrawModelName;
	std::string m_ModelName;
	Player* m_Player;
	float m_Length;
};

