/*--------------------------------------------------------------
	
	[StageObject.h]
	Author : �o���đ�

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
private:
	class Resource& m_Resource;
};

