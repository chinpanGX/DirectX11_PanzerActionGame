/*-----------------------------------------
        
    [ToonPS.hlsl]
    Author : �o���đ�

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
  
    // �����v�Z
    float light = -dot(normal.xyz, _Light.Direction.xyz);
    
    // �e�N�X�`��
    float2 uv = light;
    float3 color;
    uv = clamp(uv, 0.1f, 0.9); 
    color = g_textureToon.Sample(g_samplerState, uv).xyz;     //���邳���擾
    outDiffuse.rgb *= saturate(In.Diffuse.rgb * color);       //�e�N�X�`�� * ���_�F * ���邳
}