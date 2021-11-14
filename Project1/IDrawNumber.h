/*--------------------------------------------------------------
	
	[IDrawNumber.h]
	Author : �o���đ�

	������`�悷��C���^�[�t�F�C�X

---------------------------------------------------------------*/
#pragma once
#include "Renderer2D.h"
#include <memory>
#include <array>

class IDrawNumber
{
public:
	IDrawNumber() = delete;
	IDrawNumber(float size, int32_t digit); // �`��T�C�Y�A����
	virtual ~IDrawNumber(){}
	virtual void Draw(int32_t n) = 0; // "param" n = ���l 
	void SetColor(float r, float g, float b, float a);
protected:
	void NumberDraw(const D3DXVECTOR2& position, int32_t n);
	const float GetSize() const;
	const int32_t Getdigit() const;
private:
	D3DXVECTOR4 m_Color;
	int32_t m_digit; // ����
	float m_Size; // �`��T�C�Y
	std::unique_ptr<Renderer2D> m_Render;
	// �e�N�X�`����x���W�̃��X�g
	std::array<float, 11> m_Numbers;
};

