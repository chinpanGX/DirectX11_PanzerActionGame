/*-----------------------------------------------------------

	[Reload.h]
	リロード状態の管理
	Author : 出合翔太

------------------------------------------------------------*/
#pragma once

class Reload
{
public:
	virtual void Init() = 0; // 初期化処理
	virtual void Begin() = 0; // リロード開始
	virtual void Update() = 0; // 更新
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
	void ReloadStop();		// リロードストップ

	Player* m_Player;
	PlayerUi::Reload* m_Reload = nullptr;
	GameCommand* m_Command = nullptr;
	int32_t m_Count;
	float m_NowReloadTime; // リロード時間中
	float m_Time;
	bool m_OnReloadStop = false; // リロードストップ
	bool m_UseSkill = false; // スキルを使っているかどうか
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
	float m_NowReloadTime; // リロード時間中
};