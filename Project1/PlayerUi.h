/*-----------------------------------------------------------

	[PlayerUi.h]
	Author : 出合翔太
	プレイヤー側に表示するUI

------------------------------------------------------------*/
#pragma once
#include "Actor.h"
#include "Effect.h"

class Pause;
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
		/* 更新処理のヘルパー関数 */
		void AddGage();
		void Use();

		D3DXVECTOR4 m_Color;
		std::unique_ptr<Render> m_Render;
		Player* m_Player;
		Pause* m_Pause;

		const float m_MaxDrawSize = 400.0f;
		float m_DrawSize = 0.0f;
		float m_TimeLimit;
		float m_Time;
		float m_AddAmount; // 増加する量
		float m_SubAmount; // 減らしていく量

		bool m_Use;
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
		
		void BeginReload();			// リロード開始
		void Stop();				// リロードを止める
		void Restart();				// リスタート
		void SuccessQuickReload();	// クイックリロード成功

		// クイックリロードが有効かどうか返す
		const bool enableQuickReload()const;		
	private:
		/* 更新処理のヘルパー関数 */
		void NowReload();		// リロード優の処理
		void Finish();			// リロード終了
		void SwitchNotDraw();	// 非表示にする

		/* 描画処理のヘルパー関数 */
		void DrawIcon();

		D3DXVECTOR2 m_GagePosition;			// ゲージの位置
		D3DXVECTOR2 m_QuickRangePosition;	// クイックリロード範囲
		D3DXVECTOR2 m_IconPosition;			// アイコンの位置

		std::unique_ptr<Renderer2D> m_ReloadIcon;
		std::unique_ptr<Renderer2D> m_QuickReload;
		std::unique_ptr<Render> m_Render;
		Player* m_Player;
		Pause* m_Pause;

		// ゲージのサイズ
		const float m_MaxSize = 600.0f; // MAXサイズ
		float m_NowGage = 0.0f;			// 		
		float m_DefaultAmount;	// デフォルトの増える量
		float m_QuickAmount;	// クイックの増える量	

		float m_Time;

		bool m_DrawQuickGage = true; // 高速リロードの表示
		bool m_NowStop = false; // ストップ中かどうか
		bool m_NowReload = false; // リロード中かどうか
		bool m_EnableQuickReload = false;
		bool m_Draw = false; // 描画するかどうか
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