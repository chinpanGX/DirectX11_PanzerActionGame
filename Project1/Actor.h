/*------------------------------------------------------------
	
	[Actor.h]
	Author : 出合翔太

--------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include "Transform.h"
#include "BoxComponent.h"
#include <memory>
#include <vector>

class Component;
class Actor : public DefaultObject
{
public:
	Actor();
	virtual ~Actor();
	void Begin()override;
	// 更新処理
	void Update()override;
	// 更新後の処理
	void Event()override;
	// 描画処理
	void Draw()override;
	
	// Getter
	Transform& transform() const;
	BoxComponent& GetBoxComponent() const;
protected:
	template<typename T>
	std::unique_ptr<T> AddComponent()
	{
		if (typeid(BoxComponent) == typeid(T))
		{
			m_HasBoxComponent = true;
		}
		return std::make_unique<T>();
	}

	// コリジョン位置の更新
	void UpdateCollision(BoxComponent& BoxComponent); 
	// 行列計算
	void UpdateMatrix(Transform& Transform); 

	std::unique_ptr<Transform> m_Transform;
	std::unique_ptr<BoxComponent> m_BoxComponent;
	bool m_HasBoxComponent = false;
};
