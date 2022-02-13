/*----------------------------------------------------------

	[Renderer3D.h]
	Author : 出合翔太

-----------------------------------------------------------*/
#pragma once
#include "myLib.h"

class Graphics;
class Renderer3D final
{
public:
	Renderer3D() = delete;
	Renderer3D(Graphics& Graphics, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);
	~Renderer3D();
	void Update(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);
	void UpdeteMatrix(); // 行列計算
	void Draw();
	
	//  Distancee/頂点間の距離  untiling / テクスチャの密度の倍率, texcoord / テクスチャ座標,
	// XーＺの平面のポリゴンの作成
	void CreatePlane(float Distance = 10.0f, int UvTiling = 1, D3DXVECTOR2 Tex = D3DXVECTOR2(1.0f, 1.0f)); 
	// ＸーＹの壁の平面ポリゴン
	void CreateWall(float Distance = 10.0f, int UvTiling = 1, D3DXVECTOR2 Tex = D3DXVECTOR2(1.0f, 1.0f)); 
private:
	Graphics& m_Graphics;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Scale;
};

