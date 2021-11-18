/*------------------------------------------------------------

	[ModelPool.cpp]
	Author : 出合翔太

-------------------------------------------------------------*/
#include "Graphics.h"
#include "Engine.h"
#include "Model.h"

Prefabs::ModelPool::ModelPool(Graphics & graphics) : m_Graphics(graphics)
{
	
}

Prefabs::ModelPool::~ModelPool()
{
	// Unload処理
	for (auto itr = m_Map.begin(); itr != m_Map.end(); ++itr)
	{
		itr->second->Unload();
	}
	// クリア
	m_Map.clear();
}

void Prefabs::ModelPool::Draw(const std::string & Tag)
{
	// 描画
	m_Map[Tag]->Draw();
}

void Prefabs::ModelPool::Load(const std::string & Tag, const std::string & FileName)
{
	// 
	const std::string file = "Asset\\Model\\" + FileName; 
	m_Map[Tag] = std::make_unique<Model>(m_Graphics);
	m_Map[Tag]->Load(file);
}

void Prefabs::ModelPool::Unload(const std::string & Tag)
{
	auto itr = m_Map.find(Tag);
	if (itr != m_Map.end())
	{
		itr->second->Unload();
		itr = m_Map.erase(itr);
	}
}

void Prefabs::ModelPool::Unload()
{
	// アンロード
	for (auto itr = m_Map.begin(); itr != m_Map.end(); ++itr)
	{
		itr->second->Unload();
		itr->second.reset();
		itr->second = nullptr;
		itr = m_Map.erase(itr);
	}
	// クリア
	m_Map.clear();
	if (!m_Map.empty())
	{
		throw std::domain_error("m_Map is Not empty");
	}
}

void Prefabs::ModelPool::LoadPanzer(const std::string & Tag)
{
	m_Map[Tag + "Body"] = std::make_unique<Model>(m_Graphics);
	m_Map[Tag + "Turret"] = std::make_unique<Model>(m_Graphics);
	m_Map[Tag + "Gun"] = std::make_unique<Model>(m_Graphics);
}
