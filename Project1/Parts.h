/*-----------------------------------------------------------
	
	[Parts.h]
	Author : 出合翔太

	戦車パーツ

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
	virtual void UpdateMatrix(const D3DXMATRIX& ParentMatirx) = 0;
	const D3DXMATRIX& GetWorldMatrix() const;
protected:
	const std::string& GetTag() const;
	D3DXMATRIX m_WorldMatrix;
	class Resource& resource() const;
	class Graphics& graphics() const;
private:
	std::string m_Tagname; // タグ名
	class Resource& m_Resource;
	class Graphics& m_Graphics;
};

