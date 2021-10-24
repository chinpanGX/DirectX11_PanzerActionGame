/*-----------------------------------------------------------

	[Effect.h]
	Author : 出合翔太

	エフェクトの基底クラス

-------------------------------------------------------------*/
#pragma once
#include "Actor.h"

class Effect : public Actor
{
public:
	Effect();
	// テクスチャ座標を設定
	Effect(Math::Vector2 texMin, Math::Vector2 texMax);
	virtual ~Effect();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
protected:
	// MapとUnmapをする　
	void MapAndUnmap(float x, float y); // 引数(テクスチャ座標のx,y)
	uint32_t GetFrame() const { return m_Frame; }
	class Resource& m_Resource;
	class Graphics& m_Graphics;
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	uint32_t m_Frame;
};

