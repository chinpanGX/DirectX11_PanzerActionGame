/*--------------------------------------------------------------
	
	[Timer.h]
	Author : 出合翔太

	ゲームの制限時間を表示する　「制限時間は５分」

---------------------------------------------------------------*/
#pragma once
#include "IDrawNumber.h"
#include "DefaultObject.h"

// 分
class DrawTimerMinute final : public IDrawNumber
{
public:
	DrawTimerMinute();
	~DrawTimerMinute();
	void Draw(int32_t n)override;
};

// 秒
class DrawTimerSecond final : public IDrawNumber
{
public:
	DrawTimerSecond();
	~DrawTimerSecond();
	void Draw(int32_t n)override;
};

namespace GameBg
{
	class Timer final : public Bg
	{
	public:
		Timer();
		~Timer();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
	private:
		std::array<std::unique_ptr<IDrawNumber>, 2> m_DrawTimer;
		const float m_TimeLimit_min; // タイムリミット（分）
		int32_t m_Minute; // 分
		int32_t m_Second;	  // 秒
		float m_NowTime;  // 今の時間
		// 設定済みかどうかのフラグ
		bool m_Is1minSetColor = false;
		bool m_Is10secSetColor = false;
	};
}
