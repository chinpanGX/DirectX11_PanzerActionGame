/*--------------------------------------------------------

		[PanzerNameList.h]
		戦車の名前のリスト
		Author : 出合翔太

----------------------------------------------------------*/
#pragma once
#include "Singleton.h"
#include <vector>
#include <string>

class PanzerNameList final : public Singleton<PanzerNameList>
{
	friend Singleton<PanzerNameList>;
public:
	void Register(); // 名前の登録
	const std::vector<std::string>& GetPanzerList() const;
private:
	std::vector<std::string> m_PanzerName;
};

