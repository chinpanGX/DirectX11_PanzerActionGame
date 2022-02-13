/*------------------------------------------------------------
	
	[Actor.h]
	Author : �o���đ�

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
	// �X�V����
	void Update()override;
	// �X�V��̏���
	void Event()override;
	// �`�揈��
	void Draw()override;
	
	// Getter
	Transform& GetTransform() const;
	Collider& GetCollider() const;
protected:

	template<typename T>
	std::unique_ptr<T> AddComponent()
	{
		// �R���C�_�[�R���|�[�l���g��Add������
		if (typeid(Collider) == typeid(T))
		{
			// �R���C�_�[�������Ă��邱�Ƃ�ʒm
			m_HasCollider = true;
		}
		return std::make_unique<T>();
	}

	// �R���W�����ʒu�̍X�V
	void UpdateCollision(Collider& Collider); 
	// �s��v�Z
	void UpdateMatrix(Transform& Transform); 

	std::unique_ptr<Transform> m_Transform;
	std::unique_ptr<Collider> m_Collider;
	// �R���C�_�[�������Ă��邩�ǂ���
	bool m_HasCollider = false;
};
