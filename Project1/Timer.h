/*--------------------------------------------------------------
	
	[Timer.h]
	Author : 出合翔太

	ゲームの制限時間を表示する　「制限時間は５分」

---------------------------------------------------------------*/
#pragma once
#include "DrawNumber.h"
#include "DefaultObject.h"

// 分
class DrawTimerMinute final : public DrawNumber
{
public:
	DrawTimerMinute();
	~DrawTimerMinute();
	void Draw(int32_t value)override;
};

// 秒
class DrawTimerSecond final : public DrawNumber
{
public:
	DrawTimerSecond();
	~DrawTimerSecond();
	void Draw(int32_t value)override;
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
		std::array<std::unique_ptr<DrawNumber>, 2> m_DrawTimer;
		const float m_TimeLimitMin; // タイムリミット（分）
		int32_t m_Minute; // 分
		int32_t m_Second;	  // 秒
		float m_NowTime;  // 今の時間
		// 設定済みかどうかのフラグ
		bool m_Is1minSetColor = false;
		bool m_Is10secSetColor = false;
	};
}
