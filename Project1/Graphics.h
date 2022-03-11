/*------------------------------------------------------------
	
	[Graphics.h]
	Author : 出合翔太

	DirectX11の管理

-------------------------------------------------------------*/
#pragma once
#include "Singleton.h"
#include "stdafx.h"
#include <array>
#include <vector>

#define SAFE_RELEASE(p) do { if(p){ (p)->Release(); (p) = NULL;} } while(0)

// 頂点構造体
struct Vertex3D
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
	D3DXVECTOR4 Diffuse;
	D3DXVECTOR2 TexCoord;
};

// マテリアル構造体
struct Material
{
	Material()
	{
		ZeroMemory(this, sizeof(Material));
	}
	D3DXVECTOR4	Ambient;
	D3DXVECTOR4	Diffuse;
	D3DXVECTOR4	Specular;
	D3DXVECTOR4	Emission;
	float		Shininess;
	float		Dummy[3];//16byte境界用
};

// ライト構造体
struct Light
{
	Light()
	{
		ZeroMemory(this, sizeof(Light));
	}
	BOOL		Enable;
	BOOL		Dummy[3];//16byte境界用
	D3DXVECTOR4 Direction;
	D3DXVECTOR4 Diffuse;
	D3DXVECTOR4 Ambient;
	D3DXVECTOR4 Position;
	D3DXVECTOR4 Angle;
};

struct InstanceData
{
	D3DXMATRIX World;
};

class Graphics final
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Graphics();
	~Graphics();
	void Begin();
	void End();
	void SetAlphaToCoverageEnable(bool Enable);
	void SetDepthEnable(bool Enable);
	
	// GPUに転送
	void SetWorldViewProjection2D();
	void SetWorldMatrix(D3DXMATRIX & WorldMatrix);
	void SetViewMatrix(D3DXMATRIX & ViewMatrix);
	void SetProjectionMatrix(D3DXMATRIX & ProjectionMatrix);
	void SetMaterial(Material Material);
	void SetLight(Light Light);
	void SetCameraPosition(D3DXVECTOR3 CameraPosition);
	void SetParameter(D3DXVECTOR4 Parameter);

	// ブレンドステート
	void SetBlendStateDefault();
	void SetBlendStateAdd();
	void SetBlendStateAddAlpha();
	void SetBlendStateSub();

	// ゲッター
	const ComPtr<ID3D11Device> GetDevice() const;
	const ComPtr<ID3D11DeviceContext> GetDeviceContext() const;
private:
	// コンスタントバッファの更新
	template<typename T>
	void UpdateConstantBuffer(ComPtr<ID3D11Buffer> buffer, const T& src);

	// 初期化処理
	void SettingBlendState();
	void SettingDepthStencilState();
	void SettingSamplerState();
	void CreateConstantBuffer();
	
	ComPtr<ID3D11Device>			m_Device;
	ComPtr<ID3D11DeviceContext>		m_DeviceContext;
	ComPtr<IDXGISwapChain>			m_SwapChain;
	ComPtr<ID3D11RenderTargetView>	m_RenderTargetView;
	ComPtr<ID3D11DepthStencilView>	m_DepthStencilView;
	ComPtr<ID3D11DepthStencilState>	m_DepthStateEnable;
	ComPtr<ID3D11DepthStencilState>	m_DepthStateDisable;

	// ブレンドステート
	enum EBlendState : int32_t
	{
		BLENDSTATE_ALPHATOCOVERAGE,	 // AlphaToCoverageあり
		BLENDSTATE_NORMAL,	 // αブレンド
		BLENDSTATE_ADD,		 // 加算合成
		BLENDSTATE_ADDALPHA, // 加算合成（透過有）
		BLENDSTATE_SUB,		 // 減算合成
		BLENDSTATE_NUM_MAX
	};
	std::array<ComPtr<ID3D11BlendState>, EBlendState::BLENDSTATE_NUM_MAX> m_BlendState;
	
	// コンスタントバッファ
	enum EBuffer : int32_t
	{
		CONSTANT_BUFFER_WORLD,
		CONSTANT_BUFFER_VIEW,
		CONSTANT_BUFFER_PROJECTION,
		CONSTANT_BUFFER_MATERIAL,
		CONSTANT_BUFFER_LIGHT,
		CONSTANT_BUFFER_CAMERA,
		CONSTANT_BUFFER_PARAMETER,
		CONSTANT_BUFFER_NUM_MAX
	};
	std::vector<ComPtr<ID3D11Buffer>> m_Buffer;
};
