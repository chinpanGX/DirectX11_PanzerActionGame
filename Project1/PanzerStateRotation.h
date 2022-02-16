/*--------------------------------------------------------------

	[PanzerStateRotation.h]
	Author : 出合翔太

	回転

----------------------------------------------------------------*/
#pragma once
#include "PanzerState.h"

class Player;
namespace State
{	
	// ボディの旋回
	class BodyRotation final : public PanzerState
	{
	public:
		BodyRotation();
		~BodyRotation();
		void Begin(Player* Player)override;
		void Update(Enemy* Enemy, float DeltaTime)override;
	private:
		class Player* m_Player;
	};

	// タレットの旋回
	class TurretRotation final : public PanzerState
	{
	public:
		TurretRotation();
		~TurretRotation();
		void Begin(Player* Player)override;
		void Update(Enemy* Enemy, float DeltaTime)override;
	private:
		class Player* m_Player;
	};

	// 主砲の上下
	class GunRotation final : public PanzerState
	{
	public:
		GunRotation();
		~GunRotation();
		void Begin(Player* Player)override;
		void Update(Enemy* Enemy, float DeltaTime)override;
	};
}