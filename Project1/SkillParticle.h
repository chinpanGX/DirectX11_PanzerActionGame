/*--------------------------------------------------------------

	[SkillParticle.h]
	スキル用パーティクル
	Author : 出合翔太

---------------------------------------------------------------*/
#pragma once
#include "Actor.h"

class SkillParticle final : public Actor
{
public:
	SkillParticle();
	~SkillParticle();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;

	// life = 有効時間, position = 発生位置, color = 色
	void Create(unsigned int life, Math::Vector3 position, Math::Vector4 color);
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	class Resource& m_Resource;
	class Graphics& m_Graphics;
	Math::Vector4 m_Color; // パーティクルの色
	unsigned int m_Life; //　パーティクルを有効にする時間
};

