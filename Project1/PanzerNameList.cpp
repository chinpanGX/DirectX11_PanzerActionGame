/*--------------------------------------------------------

		[PanzerNameList.cpp]
		戦車の名前のリスト
		Author : 出合翔太

----------------------------------------------------------*/
#include "PanzerNameList.h"

void PanzerNameList::Register()
{
	m_PanzerName = { "Tiger", "Centurion", "Patton", "T-34-85", "IV-H", "Shrman" };
}

const std::vector<std::string>& PanzerNameList::GetPanzerList() const
{
	return m_PanzerName;
}
