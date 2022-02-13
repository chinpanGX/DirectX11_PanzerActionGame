/*-----------------------------------------------------------
	
	[Command.h]
	Author : �o���đ�

	�Q�[���V�[���Ŏg�����͏����̊Ǘ�

-------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include "stdafx.h"
#include <memory>
#include <vector>

namespace
{
	// false�Ȃ�}�E�X���L�[�{�[�h�Ature�Ȃ�Q�[���p�b�h
	bool g_IsInputGamePad = false;
}

// ���͏�Ԃ̎擾�ϐ�
namespace InputCode
{
	// �O��
	const int Forward = 0;
	const int Backward = 1;
	// �ˌ�
	const int Shot = 8;

	// �J�������[�h
	const int Camera = 9;

	// �⋋
	const int Replenish = 11;

}

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
	bool NowReplenishBullet() const;
private:
	void InputKeyboardAndMouse(float deltaTime);
	void InputGamePad(float deltaTime);
	// true�Ȃ���͂��Ă���/false�Ȃ���͂��Ă��Ȃ�
	std::vector<bool> m_NowInput;

	// �}�E�X�̏��
	D3DXVECTOR2 m_OldMouse;
	D3DXVECTOR2 m_Mouse;
	
	std::unique_ptr<Controller> m_Controller;
	class Player* m_Player;
	class Pause* m_Pause;
	
	bool m_NowReplenishBullet;
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
	void InputKeyBoardAndMouse();
	void InputGamePad();
	class Pause* m_Pause = nullptr;
};
