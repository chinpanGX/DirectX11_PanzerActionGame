/*------------------------------------------------------------
	
	[Fade.h]
	Author : 出合翔太

	フェード処理

--------------------------------------------------------------*/
#pragma once
#include "Bg.h"

class Fade final : public Bg
{
public:
	// フェードのステート
	enum EState
	{
		E_NONE,
		E_IN,
		E_OUT
	};

	Fade() = delete;
	Fade(class Application& App, class Resource& Res, class Fps& Fps);
	~Fade();
	
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	bool CheckStateNotNone(); // ステートがNONEならfalseを返す

	// プロパティのゲッター/セッター
	void SetNextScene(class Scene* Next);
	Scene* GetNextScene() const;
	void SetState(const EState& State);
	EState GetState() const;
private:
	static class Scene* m_Next;
	class Application& m_App;
	class Resource& m_Resource;
	class Fps& m_Fps;
	EState m_State;
	float m_Time;
	float m_Alpha;
};

