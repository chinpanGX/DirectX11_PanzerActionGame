/*---------------------------------------------------------

	[Graphics.cpp]
	Author : 出合翔太

----------------------------------------------------------*/
#include "Engine.h"
#include "Utility.h"
#include "Graphics.h"


Graphics::Graphics() :	m_Device(nullptr), m_DeviceContext(nullptr), m_SwapChain(nullptr), m_RenderTargetView(nullptr), 
						m_DepthStencilView(nullptr) ,m_DepthStateEnable(nullptr), m_DepthStateDisable(nullptr)
{
	HRESULT hr = S_OK;
	D3D_FEATURE_LEVEL featurelevel = D3D_FEATURE_LEVEL_11_0;

	// デバイス、スワップチェーン、コンテキスト生成
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = static_cast<UINT>(SCREEN_WIDTH);
	sd.BufferDesc.Height = static_cast<UINT>(SCREEN_HEIGHT);
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = Engine::Get().GetHwnd();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // alt-enter fullscreen

	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0, D3D11_SDK_VERSION, &sd,
		m_SwapChain.GetAddressOf(), m_Device.GetAddressOf(), &featurelevel, m_DeviceContext.GetAddressOf());
	ThrowIfFailed(hr, "D3D11CreateDeviceAndSwapchain");

	// レンダーターゲットビュー生成、設定
	ID3D11Texture2D* pBackBuffer = NULL;
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	m_Device->CreateRenderTargetView(pBackBuffer, NULL, m_RenderTargetView.GetAddressOf());
	pBackBuffer->Release();

	//深度ステンシル用テクスチャー作成
	ID3D11Texture2D* depthTexture = NULL;
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));
	td.Width = sd.BufferDesc.Width;
	td.Height = sd.BufferDesc.Height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc = sd.SampleDesc;
	td.Usage = D3D11_USAGE_DEFAULT;
	//td.Usage = D3D11_USAGE_DYNAMIC;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;
	m_Device->CreateTexture2D(&td, NULL, &depthTexture);

	//深度ステンシルターゲット作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = td.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Flags = 0;
	m_Device->CreateDepthStencilView(depthTexture, &dsvd, m_DepthStencilView.GetAddressOf());
	m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());

	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = static_cast<FLOAT>(SCREEN_WIDTH);
	vp.Height = static_cast<FLOAT>(SCREEN_HEIGHT);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_DeviceContext->RSSetViewports(1, &vp);

	// ラスタライザステート設定
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	// レンダリング時の描画モード
	rd.FillMode = D3D11_FILL_SOLID;
	//rd.FillMode = D3D11_FILL_WIREFRAME;
	// カリング設定しない
	rd.CullMode = D3D11_CULL_NONE;
	// 背面カリング
	//rd.CullMode = D3D11_CULL_BACK;
	rd.DepthClipEnable = TRUE;
	rd.MultisampleEnable = FALSE;

	ID3D11RasterizerState *rs;
	m_Device->CreateRasterizerState(&rd, &rs);
	m_DeviceContext->RSSetState(rs);

	// ブレンドステート設定
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_Device->CreateBlendState(&blendDesc, m_BlendState[EBlendState::BLENDSTATE_NORMAL].GetAddressOf());
	SetBlendStateDefault();

	// 加算合成
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	m_Device->CreateBlendState(&blendDesc, m_BlendState[EBlendState::BLENDSTATE_ADD].GetAddressOf());

	// 加算合成(透過有)
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	m_Device->CreateBlendState(&blendDesc, m_BlendState[EBlendState::BLENDSTATE_ADDALPHA].GetAddressOf());

	// 減算合成
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
	m_Device->CreateBlendState(&blendDesc, m_BlendState[EBlendState::BLENDSTATE_SUB].GetAddressOf());

	// 深度ステンシルステート設定
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;
	m_Device->CreateDepthStencilState(&depthStencilDesc, m_DepthStateEnable.GetAddressOf());//深度有効ステート
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	m_Device->CreateDepthStencilState(&depthStencilDesc, m_DepthStateDisable.GetAddressOf());//深度無効ステート
	m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable.Get(), NULL);

	// サンプラーステート設定
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	//samplerDesc.Filter = D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	//samplerDesc.MipLODBias = 0;
	//samplerDesc.MaxAnisotropy = 16;
	//samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	//samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	samplerDesc.MaxAnisotropy = 16;

	ID3D11SamplerState* samplerState = NULL;
	m_Device->CreateSamplerState(&samplerDesc, &samplerState);
	m_DeviceContext->PSSetSamplers(0, 1, &samplerState);

	/// 定数バッファ生成
	D3D11_BUFFER_DESC hBufferDesc{};
	hBufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	m_Device->CreateBuffer(&hBufferDesc, NULL, m_Buffer[EBuffer::CONSTANT_BUFFER_WORLD].GetAddressOf());
	m_DeviceContext->VSSetConstantBuffers(0, 1, m_Buffer[EBuffer::CONSTANT_BUFFER_WORLD].GetAddressOf());

	m_Device->CreateBuffer(&hBufferDesc, NULL, m_Buffer[EBuffer::CONSTANT_BUFFER_VIEW].GetAddressOf());
	m_DeviceContext->VSSetConstantBuffers(1, 1, m_Buffer[EBuffer::CONSTANT_BUFFER_VIEW].GetAddressOf());

	m_Device->CreateBuffer(&hBufferDesc, NULL, m_Buffer[EBuffer::CONSTANT_BUFFER_PROJECTION].GetAddressOf());
	m_DeviceContext->VSSetConstantBuffers(2, 1, m_Buffer[EBuffer::CONSTANT_BUFFER_PROJECTION].GetAddressOf());

	hBufferDesc.ByteWidth = sizeof(Material);
	m_Device->CreateBuffer(&hBufferDesc, NULL, m_Buffer[EBuffer::CONSTANT_BUFFER_MATERIAL].GetAddressOf());
	m_DeviceContext->VSSetConstantBuffers(3, 1, m_Buffer[EBuffer::CONSTANT_BUFFER_MATERIAL].GetAddressOf());

	hBufferDesc.ByteWidth = sizeof(Light);
	m_Device->CreateBuffer(&hBufferDesc, NULL,  m_Buffer[EBuffer::CONSTANT_BUFFER_LIGHT].GetAddressOf());
	m_DeviceContext->VSSetConstantBuffers(4, 1,  m_Buffer[EBuffer::CONSTANT_BUFFER_LIGHT].GetAddressOf());
	m_DeviceContext->PSSetConstantBuffers(4, 1,  m_Buffer[EBuffer::CONSTANT_BUFFER_LIGHT].GetAddressOf());

	hBufferDesc.ByteWidth = sizeof(D3DXVECTOR4);
	m_Device->CreateBuffer(&hBufferDesc, NULL,  m_Buffer[EBuffer::CONSTANT_BUFFER_CAMERA].GetAddressOf());
	m_DeviceContext->PSSetConstantBuffers(5, 1,  m_Buffer[EBuffer::CONSTANT_BUFFER_CAMERA].GetAddressOf());

	hBufferDesc.ByteWidth = sizeof(D3DXVECTOR4);
	m_Device->CreateBuffer(&hBufferDesc, NULL,  m_Buffer[EBuffer::CONSTANT_BUFFER_PARAMETER].GetAddressOf());
	m_DeviceContext->PSSetConstantBuffers(6, 1,  m_Buffer[EBuffer::CONSTANT_BUFFER_PARAMETER].GetAddressOf());

	// ライト無効化
	Light light;
	light.Enable = false;
	SetLight(light);

	// マテリアル初期化
	Material material;
	material.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);
}

Graphics::~Graphics()
{
	
}

void Graphics::Begin()
{
	// バックバッファクリア
	float ClearColor[4] = { 0.0f, 0.5f, 0.0f, 1.0f };
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), ClearColor);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Graphics::End()
{
	m_SwapChain->Present(1, 0);
}

#pragma region _SetDepthStencilSwichONOFF_
void Graphics::SetDepthEnable(bool Enable)
{
	if (Enable)
	{
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable.Get(), NULL);
	}
	else
	{
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateDisable.Get(), NULL);
	}
}
#pragma endregion _デプスステンシルの有効/無効の切り替え_

#pragma region _UpdateContantBuffer_
void Graphics::SetWorldViewProjection2D()
{
	using namespace DirectX;
	XMMATRIX world = XMMatrixIdentity();
	world = XMMatrixTranspose(world);
	UpdateConstantBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_WORLD], &world);

	XMMATRIX view = XMMatrixIdentity();
	view = XMMatrixTranspose(view);
	UpdateConstantBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_VIEW], &view);

	XMMATRIX projection = XMMatrixOrthographicOffCenterLH(0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f, 0.0f, 1.0f);
	projection = XMMatrixTranspose(projection);
	UpdateConstantBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_PROJECTION], &projection);
}

void Graphics::SetWorldMatrix(D3DXMATRIX & WorldMatrix)
{
	D3DXMATRIX world;
	D3DXMatrixTranspose(&world, &WorldMatrix);
	UpdateConstantBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_WORLD], &world);
}

void Graphics::SetViewMatrix(D3DXMATRIX & ViewMatrix)
{
	D3DXMATRIX view;
	D3DXMatrixTranspose(&view, &ViewMatrix);
	UpdateConstantBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_VIEW], &view);
}

void Graphics::SetProjectionMatrix(D3DXMATRIX & ProjectionMatrix)
{
	D3DXMATRIX proj;
	D3DXMatrixTranspose(&proj, &ProjectionMatrix);
	UpdateConstantBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_PROJECTION], &proj);
}

void Graphics::SetMaterial(Material Material)
{
	UpdateConstantBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_MATERIAL], &Material);
}

void Graphics::SetLight(Light Light)
{
	UpdateConstantBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_LIGHT], &Light);
}

void Graphics::SetCameraPosition(D3DXVECTOR3 CameraPosition)
{
	UpdateConstantBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_CAMERA], &D3DXVECTOR4(CameraPosition.x, CameraPosition.y, CameraPosition.z, 1.0f));
}

void Graphics::SetParameter(D3DXVECTOR4 Parameter)
{
	UpdateConstantBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_PARAMETER], &Parameter);
}
#pragma endregion _コンスタントバッファの更新_

#pragma region _SetBlendState_
void Graphics::SetBlendStateDefault()
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_DeviceContext->OMSetBlendState(m_BlendState[EBlendState::BLENDSTATE_NORMAL].Get(), blendFactor, 0xffffffff);
}

void Graphics::SetBlendStateAdd()
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_DeviceContext->OMSetBlendState(m_BlendState[EBlendState::BLENDSTATE_ADD].Get(), blendFactor, 0xffffffff);
}

void Graphics::SetBlendStateAddAlpha()
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_DeviceContext->OMSetBlendState(m_BlendState[EBlendState::BLENDSTATE_ADDALPHA].Get(), blendFactor, 0xffffffff);
}

void Graphics::SetBlendStateSub()
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_DeviceContext->OMSetBlendState(m_BlendState[EBlendState::BLENDSTATE_SUB].Get(), blendFactor, 0xffffffff);
}
#pragma endregion _ブレンドステートの設定_

const Microsoft::WRL::ComPtr<ID3D11Device> Graphics::GetDevice() const
{
	return m_Device;
}

const Microsoft::WRL::ComPtr<ID3D11DeviceContext> Graphics::GetDeviceContext() const
{
	return m_DeviceContext;
}

// コンスタントバッファ
template<typename T>
void Graphics::UpdateConstantBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer>  buffer, const T & src)
{
	m_DeviceContext->UpdateSubresource(buffer.Get(), 0, nullptr, src, 0, 0);
}
