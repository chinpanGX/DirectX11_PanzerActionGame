/*------------------------------------------------------------
	
	[Graphics.h]
	Author : �o���đ�

	DirectX11�̊Ǘ�

-------------------------------------------------------------*/
#pragma once
#include "Singleton.h"
#include "stdafx.h"
#include <array>
#include <vector>

#define SAFE_RELEASE(p) do { if(p){ (p)->Release(); (p) = NULL;} } while(0)

// ���_�\����
struct Vertex3D
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
	D3DXVECTOR4 Diffuse;
	D3DXVECTOR2 TexCoord;
};

// �}�e���A���\����
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
	float		Dummy[3];//16byte���E�p
};

// ���C�g�\����
struct Light
{
	Light()
	{
		ZeroMemory(this, sizeof(Light));
	}
	BOOL		Enable;
	BOOL		Dummy[3];//16byte���E�p
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
	
	// GPU�ɓ]��
	void SetWorldViewProjection2D();
	void SetWorldMatrix(D3DXMATRIX & WorldMatrix);
	void SetViewMatrix(D3DXMATRIX & ViewMatrix);
	void SetProjectionMatrix(D3DXMATRIX & ProjectionMatrix);
	void SetMaterial(Material Material);
	void SetLight(Light Light);
	void SetCameraPosition(D3DXVECTOR3 CameraPosition);
	void SetParameter(D3DXVECTOR4 Parameter);

	// �u�����h�X�e�[�g
	void SetBlendStateDefault();
	void SetBlendStateAdd();
	void SetBlendStateAddAlpha();
	void SetBlendStateSub();

	// �Q�b�^�[
	const ComPtr<ID3D11Device> GetDevice() const;
	const ComPtr<ID3D11DeviceContext> GetDeviceContext() const;
private:
	// �R���X�^���g�o�b�t�@�̍X�V
	template<typename T>
	void UpdateConstantBuffer(ComPtr<ID3D11Buffer> buffer, const T& src);

	// ����������
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

	// �u�����h�X�e�[�g
	enum EBlendState : int32_t
	{
		BLENDSTATE_ALPHATOCOVERAGE,	 // AlphaToCoverage����
		BLENDSTATE_NORMAL,	 // ���u�����h
		BLENDSTATE_ADD,		 // ���Z����
		BLENDSTATE_ADDALPHA, // ���Z�����i���ߗL�j
		BLENDSTATE_SUB,		 // ���Z����
		BLENDSTATE_NUM_MAX
	};
	std::array<ComPtr<ID3D11BlendState>, EBlendState::BLENDSTATE_NUM_MAX> m_BlendState;
	
	// �R���X�^���g�o�b�t�@
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
