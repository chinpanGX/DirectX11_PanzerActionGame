/*-----------------------------------------
        
    [ToonAnimationPS.hlsl]
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
    
    // アニメーション
    float2 uv = light;
    float3 color;
    
    // Cpu側から送信されて来るパラメータを元にUV値を変更する
    uv.x += _Parameter.x;
    uv.y = _Parameter.y;
    
    color = g_textureToon.Sample(g_samplerState, uv); //明るさを取得
    outDiffuse.rgb *= saturate(In.Diffuse.rgb * color * 1.5f); //テクスチャ * 頂点色 * 明るさ
}