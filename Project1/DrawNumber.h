/*--------------------------------------------------------------
	
	[DrawNumber.h]
	Author : 出合翔太

	数字を描画するインターフェイス

---------------------------------------------------------------*/
#pragma once
#include "Renderer2D.h"
#include <memory>
#include <array>

class DrawNumber
{
public:
	DrawNumber() = delete;
	DrawNumber(float size, int32_t digit); // 描画サイズ、桁数
	virtual ~DrawNumber(){}
	virtual void Draw(int32_t value) = 0; // "param" value = 数値 
	void SetColor(float r, float g, float b, float a);
protected:
	void NumberDraw(const D3DXVECTOR2& position, int32_t n);
	const float GetSize() const;
	const int32_t Getdigit() const;
private:
	D3DXVECTOR4 m_Color;
	int32_t m_digit; // 桁数
	float m_Size; // 描画サイズ
	std::unique_ptr<Renderer2D> m_Render;
	// テクスチャのx座標のリスト
	std::array<float, 11> m_Numbers;
};

