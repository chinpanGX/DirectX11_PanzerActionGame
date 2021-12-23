/*-------------------------------------------------
	
	[GameBg.h]
	Author : 出合翔太

--------------------------------------------------*/
#pragma once
#include "GameBg.h"

class Particle final : public Actor
{
public:
	Particle();
	~Particle();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;

	bool NotActive(); 
private:
	D3DXVECTOR4 m_Color;
	D3DXVECTOR3 m_Velocity;		// 速度
	D3DXVECTOR3 m_Acceleration; // 加速度
	std::unique_ptr<Renderer2D> m_Render;
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
	private:
		std::vector<Particle*> m_ParticleList;
		class TitleSystem* m_TitleSystem = nullptr;
	};
}