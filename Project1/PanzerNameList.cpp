/*--------------------------------------------------------

		[PanzerNameList.cpp]
		Author : 出合翔太

		戦車の名前のリスト

----------------------------------------------------------*/
#include "PanzerNameList.h"

void PanzerNameList::Register()
{
	// 戦車の名前を登録
	m_PanzerName = { "Tiger", "Centurion", "Patton", "T-34-85", "IV-H", "Shrman" };
}

const std::vector<std::string>& PanzerNameList::panzerList() const
{
	return m_PanzerName;
}
