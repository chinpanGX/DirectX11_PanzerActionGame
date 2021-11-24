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
		
		void BeginReload();
		void OnStop(); // リロードを止める
		void OffStop();

		// クイックリロード成功
		void SuccessQuickReload();
		void FailedQuickReload();

		// クイックリロードが有効かどうか返す
		const bool enableQuickReload()const;		
	private:
		// リロード終了
		void Finish();

		D3DXVECTOR4 m_IconColor; // アイコンの色
		
		D3DXVECTOR2 m_GagePosition; // ゲージの位置
		D3DXVECTOR2 m_QuickRangePosition;	// クイックリロード範囲
		D3DXVECTOR2 m_IconPosition;

		std::unique_ptr<Render> m_Render;
		Player* m_Player;

		// ゲージのサイズ
		const float m_MaxSize = 500.0f; // MAXサイズ
		float m_Center; // 画面中央
		float m_NowGage = 0.0f;			// 		
		float m_Amount; // 増える量
		
		float m_Time;

		bool m_NowStop; // ストップ中かどうか
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