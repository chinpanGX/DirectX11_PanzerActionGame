/*--------------------------------------------------------------
	
	[Pause.h]
	Author : �o���đ�

	�|�[�Y���

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
	// �|�[�Y
	void Enable();
	void Disable();
	bool GetEnable()const;

	// �X�e�[�g
	enum EState : uint32_t
	{
		KEEPON,		// ������
		OPERATION,	// ������@
		END			// �I��
	};

	void SetState(EState State);
	EState GetState()const
	{
		return m_State;
	}
	// a�l
	float GetAlpha()const;

	// �L���E�����̐؂�ւ�

	// �Q�[�����s
	void KeeponEnable();
	void KeeponDisable();

	// �Q�[��������@
	void OperationEnable();
	void OperationDisable();
	bool GetOperation() const;

	// �Q�[���I��
	void EndEnable();
	void EndDisable();
	bool GetEnd()const;

	// �I��
	void SelectTop();
	void SelectBottom();
	bool GetToporBottom();

private:
	void ChangeState(std::unique_ptr<class PauseState> State);

	std::unique_ptr<class Renderer2D> m_RenderBg; // �w�i
	std::unique_ptr<class PauseState> m_PauseState;
	EState m_State;
	float m_Alpha = 1.0f;
	float m_Changecolor = 0.01f;
	// �|�[�Y�����ǂ���
	bool m_Enable = false;
	// �Q�[���𑱂��邩
	bool m_Keepon = false;
	// ������@
	bool m_Operation = false;
	// �Q�[���I����I�񂾂�
	bool m_End = false;
	// �ォ����
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

// ������
class Keepon final : public PauseState
{
public:
	Keepon();
	void Draw(Pause* Pause)override;
};

// ������@�̊m�F
class Operation final : public PauseState
{
public:
	Operation();
	void Draw(Pause* Pause)override;
};

// �Q�[���I��
class GameEnd final : public PauseState
{
public:
	GameEnd();
	void Draw(Pause* Pause)override;
};

#pragma endregion _�|�[�Y���̃X�e�[�g_