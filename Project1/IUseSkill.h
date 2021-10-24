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
	virtual void Use(Status& status) = 0;
	virtual void Reset(Status& status) = 0;
};
