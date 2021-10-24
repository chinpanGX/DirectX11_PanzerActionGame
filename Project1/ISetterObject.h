/*--------------------------------------------------------------
	
	[ISetterObject.h]
	Author : 出合翔太

	オブジェクトをステージに設置するインターフェイス

---------------------------------------------------------------*/
#pragma once

class ISetterObject
{
public:
	virtual ~ISetterObject(){}
	virtual void Set(class Scene* scene) = 0;
};

