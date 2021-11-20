/*--------------------------------------------------------------

	[PanzerStateRotation.h]
	Author : 出合翔太

	回転

----------------------------------------------------------------*/
#pragma once
#include "PanzerState.h"

namespace State
{	
	// ボディの旋回
	class BodyRotation final : public PanzerState
	{
	public:
		BodyRotation();
		~BodyRotation();
		void Update(Cpu* pCpu, float deltaTime)override;
	private:
		float GetDirection(Cpu* pCpu); // Bodyを基準に、プレイヤーのいる方向を求める
	};

	// タレットの旋回
	class TurretRotation final : public PanzerState
	{
	public:
		TurretRotation();
		~TurretRotation();
		void Update(Cpu* pCpu, float deltaTime)override;
	private:
		float GetDirection(Cpu* pCpu); // pivotを基準に、プレイヤーがいる方向を求める
	};

	// 主砲の上下
	class GunRotation final : public PanzerState
	{
	public:
		GunRotation();
		~GunRotation();
		void Update(Cpu* pCpu, float deltaTime)override;
	};
}