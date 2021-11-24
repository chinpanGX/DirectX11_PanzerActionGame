/*-----------------------------------------------------------

	[Reload.h]
	�����[�h��Ԃ̊Ǘ�
	Author : �o���đ�

------------------------------------------------------------*/
#pragma once

class Reload
{
public:
	virtual void Begin() = 0;
	virtual void Update() = 0;
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
class GameCommand;
class Status;
class PlayerReload final : public Reload
{
public:
	PlayerReload() = delete;
	PlayerReload(const Status& status);
	~PlayerReload();
	void Begin()override;
	void Update()override;
private:
	const Status& m_Status;
	PlayerUi::Reload* m_Reload;
	GameCommand* m_Command;
	float m_NowReloadTime; // �����[�h���Ԓ�
	float m_Time;
	bool m_OnReloadStop = false; // �����[�h�X�g�b�v
};

class CpuReload : public Reload
{
public:
	CpuReload() = delete;
	CpuReload(const Status& status);
	~CpuReload();
	void Begin()override;
	void Update()override;
private:
	const Status& m_Status;
	float m_NowReloadTime; // �����[�h���Ԓ�
};