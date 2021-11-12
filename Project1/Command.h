/*-----------------------------------------------------------
	
	[Command.h]
	Author : 出合翔太

	コマンド

-------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include <memory>
#include <array>

namespace
{
	// falseならマウス＆キーボード、tureならゲームパッド
	bool g_IsInputGamePad = false;
}

// タイトル
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

// ゲームコマンド
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
	// 今入力しているか
	bool GetNowInput(int32_t i) const;
private:
	void InputKeyboard(float deltaTime);
	void InputGamePad(float deltaTime);
	// trueなら入力している/falseなら入力していない
	std::unique_ptr<Controller> m_Controller;
	class Player* m_Player;
	D3DXVECTOR2 m_OldMouse;
	D3DXVECTOR2 m_Mouse;
	std::array<bool, 10> m_NowInput;
};

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
	bool m_Select = true; // trueで戦車選択、falseでゲーム選択
	bool m_Mode;
};

// ポーズ中のコマンド
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
};