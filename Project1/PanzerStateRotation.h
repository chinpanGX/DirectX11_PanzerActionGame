/*--------------------------------------------------------------

	[PanzerStateRotation.h]
	Author : 出合翔太

	回転

----------------------------------------------------------------*/
#pragma once
#include "PanzerState.h"

namespace State
{

	class Rotation  : public PanzerState
	{
	public:
		Rotation(){}
		virtual ~Rotation(){}
		void Update(Pawn* pPawn, float deltaTime)override{}
	protected:
		float GetRightDirection(Pawn* pPawn); // ターゲットの位置が自身より右にいるか
	};

	// ボディの旋回
	class BodyRotation final : public Rotation
	{
	public:
		BodyRotation();
		~BodyRotation();
		void Update(Pawn* pPawn, float deltaTime)override;
	private:
		int32_t m_Random;
	};

	// タレットの旋回
	class TurretRotation final : public Rotation
	{
	public:
		TurretRotation();
		~TurretRotation();
		void Update(Pawn* pPawn, float deltaTime)override;
	};

	// 主砲の上下
	class GunRotation final : public Rotation
	{
	public:
		GunRotation();
		~GunRotation();
		void Update(Pawn* pPawn, float deltaTime)override;
	};
}