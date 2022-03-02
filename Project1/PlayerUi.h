/*-----------------------------------------------------------

	[PlayerUi.h]
	Author : 出合翔太
	プレイヤー側に表示するUI

------------------------------------------------------------*/
#pragma once
#include "Actor.h"
#include "Effect.h"

class Pause;
class RenderGage;
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
		std::unique_ptr<RenderGage> m_Render;
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
		const bool GetEnableQuickReload()const;		
		void SetEnableQuickReload(bool Flag);
	private:
		/* 更新処理のヘルパー関数 */
		void NowReload();			// リロードの処理
		void AddGageAndMoveIcon(float Amount);	// ゲージを増やす処理とアイコンを増やす
		void Finish();				// リロード終了
		void SwitchNotDraw();		// 非表示にする

		/* 描画処理のヘルパー関数 */
		void DrawIcon();

		D3DXVECTOR2 m_GagePosition;			// ゲージの位置
		D3DXVECTOR2 m_QuickRangePosition;	// クイックリロード範囲
		D3DXVECTOR2 m_IconPosition;			// アイコンの位置

		std::unique_ptr<Renderer2D> m_ReloadIcon;
		std::unique_ptr<Renderer2D> m_QuickReload;
		std::unique_ptr<RenderGage> m_Render;
		Player* m_Player;
		Pause* m_Pause;

		// ゲージのサイズ
		const float m_MaxSizeAmount = 600.0f; // MAXサイズ
		float m_NowGageAmount = 0.0f;			// 		
		float m_DefaultAmount;	// デフォルトの増える量
		float m_QuickAmount;	// クイックの増える量	

		float m_Time;

		bool m_DrawQuickGage = true; // 高速リロードの表示
		bool m_NowStop = false; // ストップ中かどうか
		bool m_NowReload = false; // リロード中かどうか
		bool m_EnableQuickReload = false;
		bool m_MatchCount;
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
		std::unique_ptr<RenderGage> m_Render;
		Player* m_Player;
		const float m_MaxDrawSize = 400.0f; // MAX状態HP

		// プレイヤーのHP
		float m_NowHpAmount = 0.0f; // 現在のHP
		float m_OldHpAmount = 0.0f; // 更新前のHP

		// 描画
		float m_DrawSizeAmount = 400.0f; // 現在HP
		float m_DrawRatioAmount = 0.0f; // 描画 比率		
	};
}