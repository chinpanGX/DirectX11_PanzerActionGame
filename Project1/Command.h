/*-----------------------------------------------------------
	
	[Command.h]
	Author : �o���đ�

	�R�}���h

-------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include <memory>
#include <array>

namespace
{
	// false�Ȃ�}�E�X���L�[�{�[�h�Ature�Ȃ�Q�[���p�b�h
	bool g_IsInputGamePad = false;
}

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

// �Q�[���R�}���h
class Controller;
class GameCommand final : public DefaultObject
{
public:
	GameCommand();
	~GameCommand();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	// �����͂��Ă��邩
	bool GetNowInput(int32_t i) const;
private:
	void InputKeyboard(float deltaTime);
	void InputGamePad(float deltaTime);
	// true�Ȃ���͂��Ă���/false�Ȃ���͂��Ă��Ȃ�
	std::unique_ptr<Controller> m_Controller;
	class Player* m_Player;
	D3DXVECTOR2 m_OldMouse;
	D3DXVECTOR2 m_Mouse;
	std::array<bool, 10> m_NowInput;
};

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
	bool m_Select = true; // true�Ő�ԑI���Afalse�ŃQ�[���I��
	bool m_Mode;
};

// �|�[�Y���̃R�}���h
class PauseCommand final : public DefaultObject
{
public:
	PauseCommand();
	~PauseCommand();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:
	void InputKeyBoard();
	void InputGamePad();
	class Pause* m_Pause = nullptr;
};

// ���U���g�̃R�}���h
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
};