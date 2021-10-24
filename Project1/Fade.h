/*------------------------------------------------------------
	
	[Fade.h]
	Author : 出合翔太

--------------------------------------------------------------*/
#pragma once
#include "Bg.h"

class Fade final : public Bg
{
public:
	enum EState
	{
		E_NONE,
		E_IN,
		E_OUT
	};
	Fade() = delete ;
	Fade(class Application& app, class Resource& res, class Fps& fps);
	~Fade();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	bool ChackState(); // ステートがNONEならfalseを返す

	// プロパティのゲッター/セッター
	void SetNextScene(class Scene* next);
	Scene* GetNextScene() const;
	void SetState(const EState& state);
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

