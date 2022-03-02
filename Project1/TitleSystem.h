/*--------------------------------------------------------------

	[TitleSystem.h]
	Author : 出合翔太

	タイトル画面でやる操作を管理

---------------------------------------------------------------*/
#pragma once
#include "stdafx.h"
#include "DefaultObject.h"

class TitleSystem final : public DefaultObject 
{
public:
	TitleSystem();
	~TitleSystem();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void SetState(uint32_t State);
	const uint32_t GetState() const;

	// インプットのチェック
	bool GetCheckInput();
	void EnableCheckInput();
	void DisableCheckInput();

	// ゲームパッドは使うか
	void EnableGamePad();
	void DisableGamePad();
	const bool GetInputGamePad() const;

	// どっちを選んでいるか
	// Setter
	void SelectTop();
	void SelectButtom();
	// Getter
	const bool GetSelect()const;

	// 画面ステート
	enum EState : uint32_t
	{
		BEGIN, // 最初
		SELECT,
		//SETTING_SELECT, // キーマウかパッドを選択
		CHECK_INPUT
	};
private:
	// カラーチェンジ
	void UpdateColorChenge();

	void DrawSelect();
	//void DrawSetting();
	//void DrawInput();

	std::unique_ptr<class Renderer2D> m_Render;
	D3DXVECTOR4 m_Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	float m_Alpha = 1.0f;
	uint32_t m_State;
	// コントローラを使うかどうか
	bool m_InputCheck = false;
	bool m_InputGamePad = false;
	bool m_ToporButtom = true; // true = 上、false = 下
	float m_Changecolor;
};
