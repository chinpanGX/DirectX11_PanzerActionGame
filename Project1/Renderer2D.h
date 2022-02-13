/*--------------------------------------------------------

	[Renderer2D.h]
	Author : 出合翔太

---------------------------------------------------------*/
#pragma once
#include "myLib.h"


class Graphics;
class Resource;
class Renderer2D final
{
public:
	Renderer2D() = delete;
	// テクスチャのみ設定
	Renderer2D(Graphics& Graphics, Resource& resource, const std::string& Tag);
	// プロパティ設定をすべて設定
	Renderer2D(Graphics& Graphics, Resource& resource, const std::string& Tag, const D3DXVECTOR2& pos, const D3DXVECTOR2& size, 
		const D3DXVECTOR2& ul = D3DXVECTOR2(0.0f, 0.0f), const D3DXVECTOR2& lr = D3DXVECTOR2(1.0f, 1.0f));
	~Renderer2D();

	// 頂点情報を設定する
	void SetVertex(const D3DXVECTOR2& pos, const D3DXVECTOR2& size, const D3DXVECTOR2& ul = D3DXVECTOR2(0.0f, 0.0f), const D3DXVECTOR2& lr = D3DXVECTOR2(1.0f, 1.0f), const D3DXVECTOR4& color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	// 通常の描画
	void Draw();
	// α値を変更して描画
	void Draw(float alpha);
	// ポリゴンのカラーを変更
	void Draw(const D3DXVECTOR4& color);
	// map,unmapをして描画
	void Draw(const D3DXVECTOR2& pos, const D3DXVECTOR2& size, const D3DXVECTOR2& ul = D3DXVECTOR2(0.0f, 0.0f), const D3DXVECTOR2& lr = D3DXVECTOR2(1.0f, 1.0f), 
		const D3DXVECTOR4& color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), bool ShaderSetting = true);
private:
	Graphics& m_Graphics;
	Resource& m_Resource;
	std::string m_Texture;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
};

class Render
{
public:
	Render() = delete;
	Render(Graphics& Graphics, Resource& resource);
	~Render();
	void Draw(float param, const D3DXVECTOR2& pos, const D3DXVECTOR4& color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	void Draw(float param, const D3DXVECTOR2& pos, float size_y, const std::string& texture, const D3DXVECTOR4& color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
private:
	Graphics& m_Graphics;
	Resource& m_Resource;
	std::string m_Texture;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
};
