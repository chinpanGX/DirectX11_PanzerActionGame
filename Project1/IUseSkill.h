/*----------------------------------------------------------------
	
	[IUseSkill.h]
	Author : èoçá„ƒëæ

-----------------------------------------------------------------*/
#pragma once

class Status;
class IUseSkill
{
public:
	virtual ~IUseSkill() {};
	virtual void Use(Status& Status) = 0;
	virtual void Reset(Status& Status) = 0;
};
