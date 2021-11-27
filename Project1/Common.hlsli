/*------------------------------------------
    
    [Common.hlsli]
    Autrhor : 出合翔太

--------------------------------------------*/

//マトリクスバッファ
cbuffer WorldBuffer : register(b0)
{
    matrix _World;
}
cbuffer ViewBuffer : register(b1)
{
    matrix _View;
}
cbuffer ProjectionBuffer : register(b2)
{
    matrix _Projection;
}


struct VS_IN
{
    float4 Position : POSITION0;
    float4 Normal : NORMAL0;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
};

struct PS_IN
{
    float4 Position : SV_POSITION;
    float4 WorldPosition : POSITION0;
    float4 Normal : NORMAL0;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
};

//マテリアルバッファ
struct Material
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float4 Emission;
    float Shininess;
    float3 Dummy;
};

cbuffer MaterialBuffer : register(b3)
{
    Material _Material;
}

//ライトバッファ
struct LIGHT
{
    bool Enable;
    bool3 Dummy; //16byteの境界用
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
    float4 Position;
    float4 Angle;
};

cbuffer LightBuffer : register(b4)
{
    LIGHT _Light;
}


cbuffer CameraBuffer : register(b5)
{
    float4 _CameraPosition;
}

cbuffer ParameterBuffer : register(b6)
{
    float4 _Parameter;
}
