/*--------------------------------------------------------------

	[SkillParticle.h]
	�X�L���p�p�[�e�B�N��
	Author : �o���đ�

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

	// life = �L������, position = �����ʒu, color = �F
	void Create(unsigned int life, Math::Vector3 position, Math::Vector4 color);
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	class Resource& m_Resource;
	class Graphics& m_Graphics;
	Math::Vector4 m_Color; // �p�[�e�B�N���̐F
	unsigned int m_Life; //�@�p�[�e�B�N����L���ɂ��鎞��
};

