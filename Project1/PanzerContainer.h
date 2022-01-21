/*--------------------------------------------------------------

	[PanzerContatiner.h]
	Author : 出合翔太

	戦車のデータを持っている

---------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include "GameBg.h"
#include <string>
#include <unordered_map>
#include <vector>

class Vehicle;
class PanzerContainer : public DefaultObject
{
public:
	PanzerContainer();
	~PanzerContainer();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	
	void SetChooseUp();		// 上にスクロール
	void SetChooseDown();	// 下にスクロール

	// CPU戦車を決める
	void DecisionofCpuPanzer();

	// 選択中
	const int32_t GetChose() const;
	void Reset();
	const int32_t GetButton() const;

	// プレイヤー
	const std::string& StringFindPlayerTag() const;
	// CPUのタグ
	const std::string& StringFindCpuTag()const;
private:
	static std::string m_PlayerofSelectedPanzer; // プレイヤーの選択した戦車を格納
	static std::string m_CpuofSelectedPanzer; // Cpuが選んだ戦車
	std::unordered_map<std::string, std::unique_ptr<Vehicle>> m_Map;
	std::vector<std::string> m_PanzerName;
	std::vector<float> m_TexCoord;
	std::unique_ptr<class Parameters> m_Parameters; // パラメータ表示
	std::unique_ptr<class DrawNumber> m_Number; // コスト表示
	std::unique_ptr<Renderer2D> m_SkillList;

	int32_t m_InputButton; // 1で上を選択、2で下を選択

	// 表示するパラメータ
	float m_Cost;
	float m_Hp;
	float m_Attack;
	float m_Defence;
	float m_Speed;
	float m_Reload;

	int32_t m_Choose; // どれを選んでいるのか
};