/*------------------------------------------------------------
	
	[Stage.h]
	Author : 出合翔太

	ステージクラス
	ステージに配置するクラスを設定する

-------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include "ISetterObject.h"
#include <vector>

class Stage : public DefaultObject
{
public:
	Stage() {}
	virtual ~Stage() {}
	void Begin()override {}
	void Update()override {}
	void Event()override {}
	void Draw()override {}
protected:
	// 追加
	template<typename T>
	void AddObject()
	{
		m_Object.emplace_back(std::make_unique<T>());
	}
	/// 削除
	void Remove()
	{
		m_Object.clear();
		assert(m_Object.empty());
	}
	// 設置
	void AllSet(Scene* scene)
	{
		for (auto& obj : m_Object)
		{
			obj->Set(scene);
		}
	}

	class Scene* m_Scene;
private:
	std::vector<std::unique_ptr<ISetterObject>> m_Object;
};
