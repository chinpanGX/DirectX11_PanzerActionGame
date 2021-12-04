/*-------------------------------------------------------------

	[SelectCommand.h]
	Author : �o���đ�

	��ԑI���V�[���̓��͏����̊Ǘ�

--------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"

namespace GameBg
{
	class PanzerSelectUi;
}

// ��ԑI���R�}���h�N���X
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
	bool m_Select = true; // true�Ő�ԑI���Afalse�ŃQ�[���I��
	bool m_Mode;
};
