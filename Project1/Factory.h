/*--------------------------------------------------------------

	[Factory.h]
	Author : �o���đ�

	�t�@�N�g���[

---------------------------------------------------------------*/
#pragma once
#include "myLib.h"
#include <memory>
#include <string>

namespace Factory
{
	// �r�[�N��
	class FVehicle final
	{
	public:
		enum EType: int32_t
		{
			E_PLAYER,
			E_CPU,
		};
		FVehicle();
		~FVehicle();
		std::unique_ptr<class Vehicle> Create(int32_t Type);
		std::unique_ptr<class Vehicle> Create(const std::string& name);		

	private:
		// ��Ԃ̖��O�̃��X�g
		std::vector<std::string> m_PanzerNameList; 
	};

	// ���
	class FPanzer final
	{
	public:
		std::unique_ptr<class Panzer> Create(const std::string& PanzerName);
	};

	// �p�C���b�g
	class FPivot final
	{
	public:
		std::unique_ptr<class Pivot> Create(class Vehicle& vehicle);
	};

	// �e
	class FShadow final
	{
	public:
		std::unique_ptr<class Shadow> Create();
	};
}