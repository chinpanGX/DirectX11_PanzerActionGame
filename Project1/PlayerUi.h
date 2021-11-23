/*-----------------------------------------------------------

	[PlayerUi.h]
	Author : 出合翔太
	プレイヤー側に表示するUI

------------------------------------------------------------*/
#pragma once
#include "Actor.h"
#include "Effect.h"

class Render;
class Player;
namespace PlayerUi
{	
	// スキルのゲージ
	class DrawSkill final : public Actor
	{
	public:
		DrawSkill();
		~DrawSkill();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
		void Reset();
	private:
		std::unique_ptr<Render> m_Render;
		Player* m_Player;
		const float m_MaxDrawSize = 400.0f;
		float m_DrawSize = 0.0f;
		float m_Add; // 増加する量
	};

	// リロードゲージ
	class Reload final : public Actor
	{
	public:
		Reload();
		~Reload();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
		
		void OnReload();
	private:
		D3DXVECTOR2 m_Position;
		std::unique_ptr<Render> m_Render;
		Player* m_Player;
		const float m_MaxSize = 500.0f;
		float m_NowGage = 0.0f;
		float m_Amount;
		bool m_NowReload = false; // リロード中
	};

	// Hpゲージ
	class Hp final : public Actor
	{
	public:
		Hp();
		~Hp();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
	private:
		std::unique_ptr<Render> m_Render;
		Player* m_Player;
		const float m_MaxDrawSize = 400.0f; // MAX状態HP

		// プレイヤーのHP
		float m_NowHp = 0.0f; // 現在のHP
		float m_OldHp = 0.0f; // 更新前のHP

		// 描画
		float m_DrawSize = 400.0f; // 現在HP
		float m_DrawRatio = 0.0f; // 描画 比率		
	};
}