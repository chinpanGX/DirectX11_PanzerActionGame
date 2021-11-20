/*-------------------------------------------------------------

	[CpuStateRule.h]
	CPUの動きのルール、条件を定義して管理する
	Author : 出合翔太

--------------------------------------------------------------*/
#pragma once
#include "stdafx.h"

class CpuStateRule
{
public:
	CpuStateRule();
	~CpuStateRule();
	// 更新処理
	void Update(class Cpu* pCpu);

	// 
	const int32_t behavior() const;
private:
	// エネミーとプレイヤーの距離を測る
	void PlayerToDistance(class Cpu* pCpu);
	
	//　挙動を決める
	void DecideBehavior();
	
	int32_t m_Behavior; // して欲しい挙動を示す
	float m_PlayerToDistance; // プレイヤーとの距離


	const float m_SearchRange = 50000.0f; // サーチ範囲
	const float m_ShotRange = 25000.0f;	// 射程範囲
};

