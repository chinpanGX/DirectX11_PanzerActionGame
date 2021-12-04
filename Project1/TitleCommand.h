/*-------------------------------------------------------------
	
	[TitleCommand.h]
	Author : �o���đ�

	�^�C�g���V�[���̓��͏����̊Ǘ�

--------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"

// �^�C�g��
class TitleCommand final : public DefaultObject
{
public:
	TitleCommand();
	~TitleCommand();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:
	void BeginInput();
	void InputKeyBoard();
	void InputGamePad();
	class TitleSystem* m_TitleSystem = nullptr;
};
