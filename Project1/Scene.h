/*---------------------------------------------------------

	[Scene.h]
	Author : 出合翔太

----------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include <list>
#include <vector>
#include <typeinfo>

// 更新、描画の順番
enum ELayer : int32_t
{
	LAYER_SYSTEM,
	LAYER_CAMERA,
	LAYER_3D_STAGE,
	LAYER_3D_ACTOR,
	LAYER_2D_EFFECT,
	LAYER_2D_BG,
	LAYER_2D_UI,
	LAYER_2D_PAUSE,
	LAYER_MAX,
};

class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}
	virtual void Init() = 0;
	inline virtual void Uninit()
	{
		for (int32_t i = 0; i < ELayer::LAYER_MAX; ++i)
		{
			for (auto obj : m_Object[i])
			{
				delete obj;
			}
			m_Object[i].clear();
		}
	}

	inline virtual void Update()
	{
		// 更新処理
		for (int32_t i = 0; i < ELayer::LAYER_MAX; ++i)
		{
			for (auto obj : m_Object[i])
			{
				obj->Update();
			}
		}

		// 当たり判定後のイベント
		for (size_t i = ELayer::LAYER_3D_STAGE; i <= ELayer::LAYER_2D_EFFECT; ++i)
		{
			for (auto obj : m_Object[i])
			{
				// 検知したオブジェクトののみEventを実行
				if (obj->CollisionEnter() == true)
				{
					obj->Event();
				}
			}
		}
		
		for (int32_t i = 0; i < ELayer::LAYER_MAX; ++i)
		{
			m_Object[i].remove_if([](auto obj) {return obj->Destroy(); });
		}
	}

	// 描画
	inline virtual void Draw()
	{
		for (int32_t i = LAYER_CAMERA; i < ELayer::LAYER_MAX; ++i)
		{
			for (auto obj : m_Object[i])
			{
				obj->Draw();
			}
		}
	}
	
	template <typename T>
	inline T* AddGameObject(int32_t layer)
	{
		T* obj = new T();
		m_Object[layer].push_back(obj);
		return obj;
	}
	
	template<typename T>
	inline T* GetGameObject(int32_t layer)
	{
		for (auto obj : m_Object[layer])
		{
			if (typeid(*obj) == typeid(T))
			{
				return (T*)obj;
			}
		}
		return nullptr;
	}
	
	template<typename T>
	inline std::vector<T*> GetGameObjects(int32_t layer)
	{
		std::vector<T*> v;
		for (auto obj : m_Object[layer])
		{
			if (typeid(*obj) == typeid(T))
			{
				v.push_back((T*)obj);
			}
		}
		return v;
	}

protected:
	// Init()の最後に呼び出す
	void Begin()
	{
		for (int32_t i = 0; i < ELayer::LAYER_MAX; ++i)
		{
			for (auto obj : m_Object[i])
			{
				obj->Begin();
			}
		}
	}
	// リソースのロード/アンロード
	virtual void Load() = 0;
	virtual void Unload() = 0;

	std::list<DefaultObject*> m_Object[ELayer::LAYER_MAX];
};

