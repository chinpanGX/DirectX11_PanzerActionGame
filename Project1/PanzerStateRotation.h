/*--------------------------------------------------------------

	[PanzerStateRotation.h]
	Author : �o���đ�

	��]

----------------------------------------------------------------*/
#pragma once
#include "PanzerState.h"

class Player;
namespace State
{	
	// �{�f�B�̐���
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

	// �^���b�g�̐���
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

	// ��C�̏㉺
	class GunRotation final : public PanzerState
	{
	public:
		GunRotation();
		~GunRotation();
		void Begin(Player* Player)override;
		void Update(Enemy* Enemy, float DeltaTime)override;
	};
}