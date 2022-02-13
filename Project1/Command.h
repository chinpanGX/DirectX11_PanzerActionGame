/*-----------------------------------------------------------
	
	[Command.h]
	Author : 出合翔太

	ゲームシーンで使う入力処理の管理

-------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include "stdafx.h"
#include <memory>
#include <vector>

namespace
{
	// falseならマウス＆キーボード、tureならゲームパッド
	bool g_IsInputGamePad = false;
}

// 入力状態の取得変数
namespace InputCode
{
	// 前後
	const int Forward = 0;
	const int Backward = 1;
	// 射撃
	const int Shot = 8;

	// カメラモード
	const int Camera = 9;

	// 補給
	const int Replenish = 11;

}

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
	bool NowReplenishBullet() const;
private:
	void InputKeyboardAndMouse(float deltaTime);
	void InputGamePad(float deltaTime);
	// trueなら入力している/falseなら入力していない
	std::vector<bool> m_NowInput;

	// マウスの情報
	D3DXVECTOR2 m_OldMouse;
	D3DXVECTOR2 m_Mouse;
	
	std::unique_ptr<Controller> m_Controller;
	class Player* m_Player;
	class Pause* m_Pause;
	
	bool m_NowReplenishBullet;
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
	void InputKeyBoardAndMouse();
	void InputGamePad();
	class Pause* m_Pause = nullptr;
};
