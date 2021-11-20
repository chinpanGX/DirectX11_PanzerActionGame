/*--------------------------------------------------------------

	[PanzerStateRotation.h]
	Author : �o���đ�

	��]

----------------------------------------------------------------*/
#pragma once
#include "PanzerState.h"

namespace State
{	
	// �{�f�B�̐���
	class BodyRotation final : public PanzerState
	{
	public:
		BodyRotation();
		~BodyRotation();
		void Update(Cpu* pCpu, float deltaTime)override;
	private:
		float GetDirection(Cpu* pCpu); // Body����ɁA�v���C���[�̂�����������߂�
	};

	// �^���b�g�̐���
	class TurretRotation final : public PanzerState
	{
	public:
		TurretRotation();
		~TurretRotation();
		void Update(Cpu* pCpu, float deltaTime)override;
	private:
		float GetDirection(Cpu* pCpu); // pivot����ɁA�v���C���[��������������߂�
	};

	// ��C�̏㉺
	class GunRotation final : public PanzerState
	{
	public:
		GunRotation();
		~GunRotation();
		void Update(Cpu* pCpu, float deltaTime)override;
	};
}