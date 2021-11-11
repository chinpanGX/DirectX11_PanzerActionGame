/*-----------------------------------------------------------
	
	[Parts.h]
	Author : �o���đ�

	��ԃp�[�c

------------------------------------------------------------*/
#pragma once
#include "Actor.h"
#include <string>

class Parts : public Actor
{
public:
	Parts() = delete;
	Parts(const std::string& Tag);
	void Begin()override {}
	void Update()override {}
	void Event()override {}
	void Draw()override{}
	virtual void UpdateMatrix(const DirectX::XMFLOAT4X4& ParentMatirx) = 0;
	const DirectX::XMFLOAT4X4& GetWorldMatrix() const;
protected:
	const std::string& GetTag() const;
	DirectX::XMFLOAT4X4 m_WorldMatrix;
	class Resource& resource() const;
	class Graphics& graphics() const;
private:
	std::string m_Tagname; // �^�O��
	class Resource& m_Resource;
	class Graphics& m_Graphics;
};

