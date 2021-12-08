/*-----------------------------------------------------------

	[Reload.h]
	�����[�h��Ԃ̊Ǘ�
	Author : �o���đ�

------------------------------------------------------------*/
#pragma once

class Reload
{
public:
	virtual void Init() = 0; // ����������
	virtual void Begin() = 0; // �����[�h�J�n
	virtual void Update() = 0; // �X�V
	const bool finishReload() const;
protected:
	void BeginReload();
	void FinishReload();
private:
	bool m_FinishReload = true;
};

namespace PlayerUi
{
	class Reload;
}
class Player;
class GameCommand;
class Status;
class PlayerReload final : public Reload
{
public:
	PlayerReload();
	~PlayerReload();
	void Init()override;
	void Begin()override;
	void Update()override;
private:
	void ReloadStop();		// �����[�h�X�g�b�v

	Player* m_Player;
	PlayerUi::Reload* m_Reload = nullptr;
	GameCommand* m_Command = nullptr;
	int32_t m_Count;
	float m_NowReloadTime; // �����[�h���Ԓ�
	float m_Time;
	bool m_OnReloadStop = false; // �����[�h�X�g�b�v
	bool m_UseSkill = false; // �X�L�����g���Ă��邩�ǂ���
};

class CpuReload : public Reload
{
public:
	CpuReload() = delete;
	CpuReload(const Status& status);
	~CpuReload();
	void Init()override;
	void Begin()override;
	void Update()override;
private:
	const Status& m_Status;
	float m_NowReloadTime; // �����[�h���Ԓ�
};