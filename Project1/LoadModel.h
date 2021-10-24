/*-------------------------------------------------------------
	
	[LoadModel.h]
	モデルのロードする関数
	Author : 出合翔太

--------------------------------------------------------------*/
#pragma once
#include "Loader.h"

// マテリアル構造体
struct ModelMaterial
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Texture;
	Material Material;
	char	 Name[256];
	char	 TextureName[256];
};

// 描画サブセット構造体
struct Sebset
{
	ModelMaterial Material;
	uint32_t StartIndex;
	uint32_t IndexNum;
};

// モデルの情報
struct ModelInfo
{
	Vertex3D* VertexArray;
	uint32_t  VertexNum;

	uint32_t* IndexArray;
	uint32_t  IndexNum;

	Sebset*  SubsetArray;
	uint32_t SubsetNum;
};

// モデル
class Model final : public Loader
{
public:
	Model() = delete;
	Model(Graphics & graphics);
	~Model();
	void Load(const std::string& name)override;
	void Unload();
	void Draw();
private:
	Graphics& m_Graphics;
	ComPtr<ID3D11Buffer> m_VertexBuffer;
	ComPtr<ID3D11Buffer> m_IndexBuffer;

	Sebset*	 m_SubsetArray;
	uint32_t m_SubsetNum;

	void LoadObj(const std::string& FileName, ModelInfo *Model);
	void LoadMaterial(const std::string& FileName, ModelMaterial **MaterialArray, uint32_t *MaterialNum);
};