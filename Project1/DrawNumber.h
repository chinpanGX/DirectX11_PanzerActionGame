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
	DrawNumber(float Size, int32_t Digit); // 描画サイズ、桁数
	virtual ~DrawNumber(){}
	virtual void Draw(int32_t Value) = 0; // "param" Value = 数値 
	void SetColor(float Red, float Green, float Blue, float Alpha);
protected:
	void NumberDraw(const D3DXVECTOR2& Position, int32_t Num);
	const float GetSize() const;
	const int32_t Getdigit() const;
private:
	D3DXVECTOR4 m_Color;
	int32_t m_Digit; // 桁数
	float m_Size; // 描画サイズ
	std::unique_ptr<Renderer2D> m_Render;
	// テクスチャのx座標のリスト
	std::array<float, 11> m_Numbers;
};

