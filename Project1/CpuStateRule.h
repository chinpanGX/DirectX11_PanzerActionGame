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
	
	//　挙動を決める
	void DecideBehavior();

	// エネミーとプレイヤーの距離を測る
	void PlayerToDistance(class Cpu* Cpu);

	// 
	const int32_t behavior() const;
private:
	int32_t m_Behavior; // して欲しい挙動を示す
	float m_PlayerToDistance; // プレイヤーとの距離


	const float m_SearchRange = 200.0f; // サーチ範囲
	const float m_ShotRange = 50.0f;	// 射程範囲
};

