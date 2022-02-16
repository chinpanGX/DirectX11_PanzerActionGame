/*------------------------------------------------------------
	
	[Rock.h]
	Author : èoçá„ƒëæ

--------------------------------------------------------------*/
#pragma once
#include "StageObject.h"

class GameCamera;
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
	void Create(const std::string& ModelName, D3DXVECTOR3 Position, D3DXVECTOR3 Size, float DegAngle);
private:
	std::string m_DrawModelName;
	std::string m_ModelName;
	Player* m_Player;
	GameCamera* m_Camera;
	float m_Length;
};

