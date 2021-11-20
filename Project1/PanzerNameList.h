/*--------------------------------------------------------

		[PanzerNameList.h]		
		Author : �o���đ�

		��Ԃ̖��O�̃��X�g

----------------------------------------------------------*/
#pragma once
#include "Singleton.h"
#include <vector>
#include <string>

class PanzerNameList final : public Singleton<PanzerNameList>
{
	friend Singleton<PanzerNameList>;
public:
	void Register(); // ���O�̓o�^
	// ���X�g�̎擾
	const std::vector<std::string>& panzerList() const;
private:
	std::vector<std::string> m_PanzerName;
};

