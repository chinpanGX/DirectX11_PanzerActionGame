/*--------------------------------------------------------------

	[Factory.cpp]
	Author : 出合翔太

	オブジェクト生成を管理する

---------------------------------------------------------------*/
#include "Vehicle.h"
#include "vehicle.h"
#include "Pivot.h"
#include "Shadow.h"
#include "Factory.h"
#include "PanzerContainer.h"
#include "PanzerNameList.h"
#include "PanzerList.h"

Factory::FVehicle::FVehicle()
{	
	// 戦車の名前のリストを取得
	m_PanzerNameList = PanzerNameList::Get().panzerList();
}

Factory::FVehicle::~FVehicle()
{
}

// ビークル
std::unique_ptr<class Vehicle> Factory::FVehicle::Create(int32_t Type)
{
	// 一時保存
	std::unique_ptr<Vehicle> tmp = nullptr;
	PanzerContainer pc;
	// CPU側に設定する戦車を決める
	pc.DecisionofCpuPanzer();
	switch (Type)
	{
	case EType::E_PLAYER:
		tmp = Create(pc.StringFindPlayerTag());
		return tmp;
		break;
	case EType::E_CPU:
		tmp = Create(pc.StringFindCpuTag());
		return tmp;
		break;
	}
	return nullptr;
}

std::unique_ptr<class Vehicle> Factory::FVehicle::Create(const std::string & Name)
{
	// 戦車のリストから一致したものをつくる
	if (Name == m_PanzerNameList[0])
	{
		return std::make_unique<Tiger>();
	}
	else if (Name == m_PanzerNameList[1])
	{
		return std::make_unique<Centurion>();
	}
	else if (Name == m_PanzerNameList[2])
	{
		return std::make_unique<Patton>();
	}
	else if (Name == m_PanzerNameList[3])
	{
		return std::make_unique<T_34_85>();
	}
	else if (Name == m_PanzerNameList[4])
	{
		return std::make_unique<IV_H>();
	}
	else if(Name == m_PanzerNameList[5])
	{
		return std::make_unique<Sherman>();
	}

	return nullptr;
}

// 戦車
std::unique_ptr<class Panzer> Factory::FPanzer::Create(const std::string & PanzerName)
{
	return std::make_unique<Panzer>(PanzerName);
}

// 戦車
std::unique_ptr<class Pivot> Factory::FPivot::Create(Vehicle & Vehicle)
{
	//　パイロットの設定
	std::unique_ptr<Pivot> tmp = std::make_unique<Pivot>(Vehicle);
	auto pos = Vehicle.GetBodyTransform().GetPosition();
	pos.y += 5.0f;
	
	// 初期位置の設定
	tmp->GetTransform().SetPosition(pos);
	tmp->GetTransform().SetRotation(Vehicle.GetBodyTransform().GetRotation());
	return tmp;
}

// 影
std::unique_ptr<class Shadow> Factory::FShadow::Create()
{
	return std::make_unique<Shadow>();
}
