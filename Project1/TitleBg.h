/*-------------------------------------------------
	
	[GameBg.h]
	Author : 出合翔太

--------------------------------------------------*/
#pragma once
#include "GameBg.h"

class TitleSystem;
// タイトル画面のパーティクル
class Particle final : public Actor
{
public:
	Particle();
	~Particle();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void titleSystem(TitleSystem* p);
private:
	void BeginGenerateOtherBeginScene();
	void Begin(float x, float y, float vx, float vy, float ax, float ay);

	D3DXVECTOR4 m_Color;
	D3DXVECTOR3 m_Velocity;		// 速度
	D3DXVECTOR3 m_Acceleration; // 加速度
	D3DXVECTOR2 m_Size;
	std::unique_ptr<Renderer2D> m_Render;
	TitleSystem* m_TitleSystem;
	int32_t m_Life;
	static int32_t m_BeginTypetoGenerateOtherBeginScene;
};

namespace GameBg
{
	//タイトル背景
	class TitleBg final : public Bg
	{
	public:
		TitleBg();
		~TitleBg();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
		void titleSystem(TitleSystem* p);
	private:
		std::vector<Particle*> m_ParticleList;
		TitleSystem* m_TitleSystem = nullptr;
		uint32_t m_State;
	};
}