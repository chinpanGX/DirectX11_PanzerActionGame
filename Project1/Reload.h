/*-----------------------------------------------------------

	[Reload.h]
	リロード状態の管理
	Author : 出合翔太

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
	float m_NowReloadTime; // リロード時間中
	float m_Time;
	bool m_OnReloadStop = false; // リロードストップ
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
	float m_NowReloadTime; // リロード時間中
};