/*-------------------------------------------------------------
	
	[TitleCommand.h]
	Author : 出合翔太

	タイトルシーンの入力処理の管理

--------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"

// タイトル
class TitleCommand final : public DefaultObject
{
public:
	TitleCommand();
	~TitleCommand();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:
	void BeginInput();
	void InputKeyBoard();
	void InputGamePad();
	class TitleSystem* m_TitleSystem = nullptr;
};
