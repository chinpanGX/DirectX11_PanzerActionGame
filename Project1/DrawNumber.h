/*--------------------------------------------------------------
	
	[DrawNumber.h]
	Author : �o���đ�

	������`�悷��C���^�[�t�F�C�X

---------------------------------------------------------------*/
#pragma once
#include "Renderer2D.h"
#include <memory>
#include <array>

class DrawNumber
{
public:
	DrawNumber() = delete;
	DrawNumber(float Size, int32_t Digit); // �`��T�C�Y�A����
	virtual ~DrawNumber(){}
	virtual void Draw(int32_t Value) = 0; // "param" Value = ���l 
	void SetColor(float Red, float Green, float Blue, float Alpha);
protected:
	void NumberDraw(const D3DXVECTOR2& Position, int32_t Num);
	const float GetSize() const;
	const int32_t Getdigit() const;
private:
	D3DXVECTOR4 m_Color;
	int32_t m_Digit; // ����
	float m_Size; // �`��T�C�Y
	std::unique_ptr<Renderer2D> m_Render;
	// �e�N�X�`����x���W�̃��X�g
	std::array<float, 11> m_Numbers;
};

