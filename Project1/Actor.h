/*------------------------------------------------------------
	
	[Actor.h]
	Author : 出合翔太

--------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include "Transform.h"
#include "Collider.h"
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
	Transform& GetTransform() const;
	Collider& GetCollider() const;
protected:

	template<typename T>
	std::unique_ptr<T> AddComponent()
	{
		// コライダーコンポーネントをAddしたら
		if (typeid(Collider) == typeid(T))
		{
			// コライダーを持っていることを通知
			m_HasCollider = true;
		}
		return std::make_unique<T>();
	}

	// コリジョン位置の更新
	void UpdateCollision(Collider& Collider); 
	// 行列計算
	void UpdateMatrix(Transform& Transform); 

	std::unique_ptr<Transform> m_Transform;
	std::unique_ptr<Collider> m_Collider;
	// コライダーを持っているかどうか
	bool m_HasCollider = false;
};
