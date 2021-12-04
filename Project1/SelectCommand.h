/*-------------------------------------------------------------

	[SelectCommand.h]
	Author : 出合翔太

	戦車選択シーンの入力処理の管理

--------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"

namespace GameBg
{
	class PanzerSelectUi;
}

// 戦車選択コマンドクラス
class SelectCommand final : public DefaultObject
{
public:
	SelectCommand();
	~SelectCommand();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	const bool GetSelect()const;
private:
	void InputKeyBoard();
	void InputGamePad();
	class PanzerContainer* m_Container = nullptr;
	class GameBg::PanzerSelectUi* m_Ui;
	bool m_Select = true; // trueで戦車選択、falseでゲーム選択
	bool m_Mode;
};
