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
	Renderer2D(Graphics& graphics, Resource& resource, const std::string& Tag);
	// プロパティ設定をすべて設定
	Renderer2D(Graphics& graphics, Resource& resource, const std::string& Tag, const Math::Vector2& pos, const Math::Vector2& size, 
		const Math::Vector2& ul = Math::Vector2(0.0f, 0.0f), const Math::Vector2& lr = Math::Vector2(1.0f, 1.0f));
	~Renderer2D();

	// 頂点情報を設定する
	void SetVertex(const Math::Vector2& pos, const Math::Vector2& size, const Math::Vector2& ul = Math::Vector2(0.0f, 0.0f), const Math::Vector2& lr = Math::Vector2(1.0f, 1.0f));

	// 通常の描画
	void Draw();
	// α値を変更して描画
	void Draw(float alpha);
	// ポリゴンのカラーを変更
	void Draw(const Math::Vector4& color);
	// map,unmapをして描画
	void Draw(const Math::Vector2& pos, const Math::Vector2& size, const Math::Vector2& ul = Math::Vector2(0.0f, 0.0f), const Math::Vector2& lr = Math::Vector2(1.0f, 1.0f), 
		const Math::Vector4& color = Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
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
	Render(Graphics& graphics, Resource& resource);
	~Render();
	void Draw(float Param, const Math::Vector2& pos, const Math::Vector4& color = Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
private:
	Graphics& m_Graphics;
	Resource& m_Resource;
	std::string m_Texture;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
};
