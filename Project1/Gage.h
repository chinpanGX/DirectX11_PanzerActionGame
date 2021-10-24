/*--------------------------------------------------------------
	
	[Gage.h]
	Author : o‡ãÄ‘¾

	Ÿr–ÅƒQ[ƒW‚Ì•\¦

---------------------------------------------------------------*/
#pragma once
#include "Bg.h"
#include "Manager.h"

// Ÿr–ÅƒQ[ƒW‚ÌŠÇ—
class RemainGage final : public IManager
{
public:
	RemainGage();
	~RemainGage();
	void Update(GameManager* manager, Pawn* pawn, int32_t type)override;
	const float GetGage(int32_t type) const;
private:
	void SetGage(float gage, int32_t type);
	float m_EmenyGage = 1000.0f;
	float m_PlayerGage = 1000.0f;
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
		std::unique_ptr<class Render> m_Render;
	};
}