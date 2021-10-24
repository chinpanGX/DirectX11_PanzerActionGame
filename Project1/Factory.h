/*--------------------------------------------------------------

	[Factory.h]
	Author : 出合翔太

	ファクトリー

---------------------------------------------------------------*/
#pragma once
#include "myLib.h"
#include <memory>
#include <string>

namespace Factory
{
	// ビークル
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
		
		// 戦車の登録リスト
		const std::vector<std::string>& GetPanzerNameList() const;

	private:
		// 戦車の名前のリスト
		std::vector<std::string> m_PanzerNameList; 
	};

	// 戦車
	class FPanzer final
	{
	public:
		std::unique_ptr<class Panzer> Create(const std::string& PanzerName);
	};

	// パイロット
	class FPilot final
	{
	public:
		std::unique_ptr<class PanzerPilot> Create(class Vehicle& vehicle);
	};

	// 影
	class FShadow final
	{
	public:
		std::unique_ptr<class Shadow> Create();
	};
}