/*--------------------------------------------------------------
	
	[Pause.h]
	Author : 出合翔太

	ポーズ画面

---------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include "Renderer2D.h"
#include <memory>
#include <array>

class Renderer2D;
class Pause : public DefaultObject
{
public:
	Pause();
	~Pause();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	// ポーズ
	void Enable();
	void Disable();
	bool GetEnable()const;

	// ステート
	enum EState : uint32_t
	{
		KEEPON,		// 続ける
		OPERATION,	// 操作方法
		END			// 終了
	};

	void SetState(EState State);
	EState GetState()const
	{
		return m_State;
	}
	// a値
	float GetAlpha()const;

	// 有効・無効の切り替え

	// ゲーム続行
	void KeeponEnable();
	void KeeponDisable();

	// ゲーム操作方法
	void OperationEnable();
	void OperationDisable();
	bool GetOperation() const;

	// ゲーム終了
	void EndEnable();
	void EndDisable();
	bool GetEnd()const;

	// 選択
	void SelectTop();
	void SelectBottom();
	bool GetToporBottom();

private:
	void ChangeState(std::unique_ptr<class PauseState> State);

	std::unique_ptr<class Renderer2D> m_RenderBg; // 背景
	std::unique_ptr<class PauseState> m_PauseState;
	EState m_State;
	float m_Alpha = 1.0f;
	float m_Changecolor = 0.01f;
	// ポーズ中かどうか
	bool m_Enable = false;
	// ゲームを続けるか
	bool m_Keepon = false;
	// 操作方法
	bool m_Operation = false;
	// ゲーム終了を選んだか
	bool m_End = false;
	// 上か下か
	bool m_TopToBottom = true;
};

#pragma region _PauseState_
// State
class PauseState
{
public:
	PauseState();
	virtual ~PauseState(){}
	virtual void Draw(Pause* Pause) = 0;
protected:
	class Renderer2D& GetRenderer() const;
private:
	std::shared_ptr<class Renderer2D> m_Renderer; // Ui
};

// 続ける
class Keepon final : public PauseState
{
public:
	Keepon();
	void Draw(Pause* Pause)override;
};

// 操作方法の確認
class Operation final : public PauseState
{
public:
	Operation();
	void Draw(Pause* Pause)override;
};

// ゲーム終了
class GameEnd final : public PauseState
{
public:
	GameEnd();
	void Draw(Pause* Pause)override;
};

#pragma endregion _ポーズ中のステート_