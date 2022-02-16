/*-------------------------------------------------
	
	[GameBg.h]
	Author : �o���đ�

--------------------------------------------------*/
#pragma once
#include "GameBg.h"

class TitleSystem;
// �^�C�g����ʂ̃p�[�e�B�N��
class TitleParticle final : public Actor
{
public:
	TitleParticle();
	~TitleParticle();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	void SetTitleSystem(TitleSystem* Title);
private:
	void Generate();
	void Begin(float x, float y, float vx, float vy, float ax, float ay);

	D3DXVECTOR4 m_Color;
	D3DXVECTOR3 m_Velocity;		// ���x
	D3DXVECTOR3 m_Acceleration; // �����x
	D3DXVECTOR2 m_Size;
	std::unique_ptr<Renderer2D> m_Render;
	TitleSystem* m_TitleSystem;
	int32_t m_Life;
	static int32_t m_TypeToGenerate;
};

namespace GameBg
{
	//�^�C�g���w�i
	class TitleBg final : public Bg
	{
	public:
		TitleBg();
		~TitleBg();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
		void SetTitleSystem(TitleSystem* Title);
	private:
		std::vector<TitleParticle*> m_ParticleList;
		TitleSystem* m_TitleSystem = nullptr;
		uint32_t m_State;
	};
}