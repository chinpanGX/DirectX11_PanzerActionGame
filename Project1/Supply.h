/*-------------------------------------------------------------

	[Supply.h]
	Author : o‡ãÄ‘¾

	•â‹‹’n“_

--------------------------------------------------------------*/
#pragma once
#include "StageObject.h"

class Supply final : public StageObject
{
public:
	Supply();
	~Supply();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};

