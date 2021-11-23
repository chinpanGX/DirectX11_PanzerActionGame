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
	std::unique_ptr<Reload> m_Reload;
	float m_NowReloadTime; // リロード時間中
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
	std::unique_ptr<Reload> m_Reload;
	float m_NowReloadTime; // リロード時間中
};