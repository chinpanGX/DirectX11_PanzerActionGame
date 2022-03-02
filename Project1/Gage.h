/*--------------------------------------------------------------
	
	[Gage.h]
	Author : o‡ãÄ‘¾

	Ÿr–ÅƒQ[ƒW‚Ì•\¦

---------------------------------------------------------------*/
#pragma once
#include "Bg.h"
#include "Manager.h"

namespace GameBg
{
	class DrawGage;
}

// Ÿr–ÅƒQ[ƒW‚ÌŠÇ—
class RemainGage final : public IManager
{
public:
	RemainGage();
	~RemainGage();
	void Begin()override;
	void Update(GameManager* Manager, Pawn* Pawn, int32_t Type)override;
	const float GetGage(int32_t Type) const;
private:
	void SetGage(float gage, int32_t Type);
	float m_EmenyGage = 1000.0f;
	float m_PlayerGage = 1000.0f;
	GameBg::DrawGage* m_Gage;
};

// Ÿr–ÅƒQ[ƒW‚ğ•`‰æ‚·‚é
namespace GameBg
{
	class DrawGage : public Bg
	{
	public:
		DrawGage();
		~DrawGage();
		void Update()override;
		void Event()override;
		void Draw()override;
		void SetEnemyGage(float f);
		void SetPlayerGage(float f);
	private:
		float m_EmenyGage = 1000.0f;
		float m_PlayerGage = 1000.0f;
		std::unique_ptr<class RenderGage> m_Render;
	};
}