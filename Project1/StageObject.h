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
	class Resource& GetResource()const;
	// ���a
	void SetRadius(float Radius);
	float GetRadius() const;
private:
	class Resource& m_Resource;
	float m_Radius; // �傫���̔��a
};

