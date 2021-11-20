/*--------------------------------------------------------

		[PanzerNameList.h]		
		Author : 出合翔太

		戦車の名前のリスト

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
	// リストの取得
	const std::vector<std::string>& panzerList() const;
private:
	std::vector<std::string> m_PanzerName;
};

