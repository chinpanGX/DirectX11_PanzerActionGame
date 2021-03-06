/*-------------------------------------------------------------

	[SelectCommand.h]
	Author : oγΔΎ

	νΤIπV[ΜόΝΜΗ

--------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"

namespace GameBg
{
	class PanzerSelectUi;
}

// νΤIπR}hNX
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
	bool m_Select = true; // trueΕνΤIπAfalseΕQ[Iπ
	bool m_Mode;
	bool m_Enter;
};
