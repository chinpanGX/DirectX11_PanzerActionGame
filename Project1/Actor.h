/*------------------------------------------------------------
	
	[Actor.h]
	Author : �o���đ�

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
	// �X�V����
	void Update()override;
	// �X�V��̏���
	void Event()override;
	// �`�揈��
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

	// �R���W�����ʒu�̍X�V
	void UpdateCollision(BoxComponent& BoxComponent); 
	// �s��v�Z
	void UpdateMatrix(Transform& Transform); 

	std::unique_ptr<Transform> m_Transform;
	std::unique_ptr<BoxComponent> m_BoxComponent;
	bool m_HasBoxComponent = false;
};
