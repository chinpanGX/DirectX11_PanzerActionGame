/*------------------------------------------------------------
	
	[Graphics.h]
	Author : 出合翔太

	DirectX11の管理

-------------------------------------------------------------*/
#pragma once
#include "Singleton.h"
#include "stdafx.h"
#include <array>

#define SAFE_RELEASE(p) do { if(p){ (p)->Release(); (p) = NULL;} } while(0)

// 頂点構造体
struct Vertex3D
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT3 Normal;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT2 TexCoord;
};

// マテリアル構造体
struct Material
{
	Material()
	{
		ZeroMemory(this, sizeof(Material));
	}
	DirectX::XMFLOAT4	Ambient;
	DirectX::XMFLOAT4	Diffuse;
	DirectX::XMFLOAT4	Specular;
	DirectX::XMFLOAT4	Emission;
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
	DirectX::XMFLOAT4 Direction;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Ambient;
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
	void SetDepthEnable(bool Enable);
	void SetWorldViewProjection2D();
	void SetWorldMatrix(DirectX::XMMATRIX & WorldMatrix);
	void SetViewMatrix(DirectX::XMMATRIX & ViewMatrix);
	void SetProjectionMatrix(DirectX::XMMATRIX & ProjectionMatrix);
	void SetMaterial(Material Material);
	void SetLight(Light Light);
	void SetCameraPosition(DirectX::XMFLOAT3 CameraPosition);
	void SetParameter(DirectX::XMFLOAT4 Parameter);
	void SetBlendStateDefault();
	void SetBlendStateSub();

	const ComPtr<ID3D11Device> GetDevice() const;
	const ComPtr<ID3D11DeviceContext> GetDeviceContext() const;
private:
	// コンスタントバッファの更新
	template<typename T>
	void UpdateCBuffer(ComPtr<ID3D11Buffer> buffer, const T& src);
	
	ComPtr<ID3D11Device>			m_Device;
	ComPtr<ID3D11DeviceContext>		m_DeviceContext;
	ComPtr<IDXGISwapChain>			m_SwapChain;
	ComPtr<ID3D11RenderTargetView>	m_RenderTargetView;
	ComPtr<ID3D11DepthStencilView>	m_DepthStencilView;
	ComPtr<ID3D11DepthStencilState>	m_DepthStateEnable;
	ComPtr<ID3D11DepthStencilState>	m_DepthStateDisable;
	std::array<ComPtr<ID3D11BlendState>, 2> m_BlendState;
	
	enum EBuffer : int32_t
	{
		CONSTANT_BUFFER_WORLD,
		CONSTANT_BUFFER_VIEW,
		CONSTANT_BUFFER_PROJECTION,
		CONSTANT_BUFFER_MATERIAL,
		CONSTANT_BUFFER_LIGHT,
		CONSTANT_BUFFER_CAMERA,
		CONSTANT_BUFFER_PARAMETER,
		NUM_MAX
	};
	std::array<ComPtr<ID3D11Buffer>, EBuffer::NUM_MAX> m_Buffer;
};
