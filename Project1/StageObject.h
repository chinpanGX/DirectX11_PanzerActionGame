/*--------------------------------------------------------------
	
	[StageObject.h]
	Author : èoçá„ƒëæ

---------------------------------------------------------------*/
#pragma once
#include "Actor.h"

class StageObject : public Actor
{
public:
	StageObject();
	virtual ~StageObject();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
protected:
	class Resource& resource()const;
	// îºåa
	void redius(float r);
	float radius() const;
private:
	class Resource& m_Resource;
	float m_Radius;
};

