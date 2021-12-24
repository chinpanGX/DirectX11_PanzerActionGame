/*-------------------------------------------------
	
	[GameBg.h]
	Author : 出合翔太

--------------------------------------------------*/
#pragma once
#include "GameBg.h"

class TitleSystem;
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
	void Begin(float x, float y, float vx, float vy, float ax, float ay);
	void Velocity(float x, float y);
	void Acceleration(float x, float y);
	bool NotActive(); 
private:
	D3DXVECTOR4 m_Color;
	D3DXVECTOR3 m_Velocity;		// 速度
	D3DXVECTOR3 m_Acceleration; // 加速度
	std::unique_ptr<Renderer2D> m_Render;
	TitleSystem* m_TitleSystem;
	int32_t m_Life;
	float m_Angle;
	bool m_Active;
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