/*--------------------------------------------------------

		[PanzerNameList.cpp]
		Author : �o���đ�

		��Ԃ̖��O�̃��X�g

----------------------------------------------------------*/
#include "PanzerNameList.h"

void PanzerNameList::Register()
{
	// ��Ԃ̖��O��o�^
	m_PanzerName = { "Tiger", "Centurion", "Patton", "T-34-85", "IV-H", "Shrman" };
}

const std::vector<std::string>& PanzerNameList::panzerList() const
{
	return m_PanzerName;
}
