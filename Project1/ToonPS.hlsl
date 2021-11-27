/*-----------------------------------------
        
    [ToonPS.hlsl]
    Author : 出合翔太

------------------------------------------*/
#include "Common.hlsli"

Texture2D g_texture : register(t0);
Texture2D g_textureToon : register(t1);
SamplerState g_samplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_TARGET)
{
    float4 normal = normalize(In.Normal);
   
    outDiffuse = g_texture.Sample(g_samplerState, In.TexCoord);
    outDiffuse.a *= In.Diffuse.a;
  
    // 光源計算
    float light = -dot(normal.xyz, _Light.Direction.xyz);
    
    // テクスチャ
    float2 uv = light;
    float3 color;
    uv = clamp(uv, 0.1f, 0.9); 
    color = g_textureToon.Sample(g_samplerState, uv).xyz;     //明るさを取得
    outDiffuse.rgb *= saturate(In.Diffuse.rgb * color);       //テクスチャ * 頂点色 * 明るさ
}