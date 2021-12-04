/*-------------------------------------------------------------

	[ResultCommand.h]
	Author : 出合翔太

	リザルトシーンの入力処理の管理

--------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include "stdafx.h"

namespace GameBg
{
	class ResultBg;
}

// リザルトのコマンド
class ResultCommand final : public DefaultObject
{
public:
	ResultCommand();
	~ResultCommand();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:
	void InputKeyBoard();
	void InputGamePad();
	int32_t m_Frame = 0;
	GameBg::ResultBg* m_Bg;
};